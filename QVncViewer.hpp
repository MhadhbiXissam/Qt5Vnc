#ifndef QVNCVIEWER_HPP
#define QVNCVIEWER_HPP
#include <iostream>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <thread>
#include <string>
#include <QImage>
#include <rfb/rfbclient.h>

class QVncViewer : public QWidget
{
    Q_OBJECT

public:
    explicit QVncViewer(QWidget *parent = nullptr);
    virtual ~QVncViewer();
    void start();
    void setServerDetails(const std::string &ip, int port);
    std::string serverIp;
    int serverPort;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    bool m_startFlag = false;
    QImage m_image;
    rfbClient *cl;
    std::thread *m_vncThread;
    static void finishedFramebufferUpdateStatic(rfbClient *cl);
    void finishedFramebufferUpdate(rfbClient *cl);
};

#endif // QVNCVIEWER_HPP
