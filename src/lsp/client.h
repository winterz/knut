#pragma once

#include "requests.h"

#include <QObject>

#include <spdlog/spdlog.h>

#include <functional>
#include <unordered_map>

class QProcess;

namespace Lsp {

class Client : public QObject
{
    Q_OBJECT

public:
    Client(const std::string &language, QString program, QStringList arguments, QObject *parent = nullptr);

    bool start();
    bool shutdown();

    template <typename Request>
    void sendAsyncRequest(const Request &request, typename Request::ResponseCallback callback)
    {
        m_callbacks[request.id] = [this, callback](nlohmann::json &&j) {
            if (callback) {
                auto response = deserializeResponse<typename Request::Response>(std::move(j));
                callback(std::move(response));
            }
        };
        sendAsyncJsonRequest(request);
    }

    template <typename Request>
    typename Request::Response sendRequest(const Request &request)
    {
        m_callbacks[request.id] = [this](nlohmann::json &&j) {
            m_response = std::move(j);
            emit responseEmitted({});
        };

        auto j = sendJsonRequest(request);
        return deserializeResponse<typename Request::Response>(std::move(j));
    }

    template <typename Notification>
    void sendNotification(const Notification &notification)
    {
        sendJsonNotification(notification);
    }

signals:
    void initialized();
    void finished();
    void errorOccured(int error);
    void responseEmitted(QPrivateSignal);

private:
    void readError();
    void readOutput();
    void handleError(int error);

    template <typename Response>
    Response deserializeResponse(nlohmann::json &&j)
    {
        try {
            return j.get<Response>();
        } catch (...) {
            m_serverLogger->error("==> Invalid response from server: {}", j.dump());
        }
        return {};
    }

    void sendAsyncJsonRequest(nlohmann::json jsonRequest);
    nlohmann::json sendJsonRequest(nlohmann::json jsonRequest);
    void sendJsonNotification(nlohmann::json jsonNotification);

    bool initialize();
    bool initializeCallback(InitializeRequest::Response response);
    bool shutdownCallback(ShutdownRequest::Response response);

    void logMessage(std::string type, const nlohmann::json &message);

private:
    std::shared_ptr<spdlog::logger> m_serverLogger;
    std::shared_ptr<spdlog::logger> m_messageLogger;
    const QString m_program;
    const QStringList m_arguments;
    QProcess *m_process = nullptr;

    std::unordered_map<MessageId, std::function<void(nlohmann::json)>> m_callbacks;
    nlohmann::json m_response;
};

}
