

#include "QVncViewer.hpp"

QVncViewer::QVncViewer(QWidget *parent)
    : QWidget(parent),
      m_startFlag(false),
      cl(nullptr),
      m_vncThread(nullptr),
      serverPort(0) {
    // Initialization code for the widget, e.g. setting default values
}

void QVncViewer::finishedFramebufferUpdateStatic(rfbClient *cl)
{
    QVncViewer *ptr = static_cast<QVncViewer*>(rfbClientGetClientData(cl, nullptr));
    ptr->finishedFramebufferUpdate(cl);
}

void QVncViewer::finishedFramebufferUpdate(rfbClient *cl)
{
    m_image = QImage(cl->frameBuffer, cl->width, cl->height, QImage::Format_RGB16);

    update();
}

void QVncViewer::paintEvent(QPaintEvent *event)
{
    event->accept();

    QPainter painter(this);
    painter.drawImage(this->rect(), m_image);
}

void QVncViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (m_startFlag) {
        SendPointerEvent(cl,
                         event->localPos().x() / width() * cl->width,
                         event->localPos().y() / height() * cl->height,
                         (event->buttons() & Qt::LeftButton) ? 1 : 0);
    }
}

void QVncViewer::mousePressEvent(QMouseEvent *event)
{
    if (m_startFlag) {
        SendPointerEvent(cl,
                         event->localPos().x() / width() * cl->width,
                         event->localPos().y() / height() * cl->height,
                         1);
    }
}

void QVncViewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_startFlag) {
        SendPointerEvent(cl,
                         event->localPos().x() / width() * cl->width,
                         event->localPos().y() / height() * cl->height,
                         0);
    }
}

void QVncViewer::closeEvent(QCloseEvent *event)
{
    m_startFlag = false;
    if (m_vncThread->joinable()) {
        m_vncThread->join();
    }
    QWidget::closeEvent(event);
}

void QVncViewer::start()
{
    cl = rfbGetClient(8, 3, 4);
    cl->format.depth = 24;
    cl->format.depth = 16;
    cl->format.bitsPerPixel = 16;
    cl->format.redShift = 11;
    cl->format.greenShift = 5;
    cl->format.blueShift = 0;
    cl->format.redMax = 0x1f;
    cl->format.greenMax = 0x3f;
    cl->format.blueMax = 0x1f;
    cl->appData.compressLevel = 9;
    cl->appData.qualityLevel = 1;
    cl->appData.encodingsString = "tight ultra";
    cl->FinishedFrameBufferUpdate = finishedFramebufferUpdateStatic;
    cl->serverHost = strdup(serverIp.c_str());
    cl->serverPort = serverPort;
    cl->appData.useRemoteCursor = TRUE;

    rfbClientSetClientData(cl, nullptr, this);

    if (rfbInitClient(cl, 0, nullptr)) {
    } else {
        std::cout << "[INFO] disconnected" << std::endl;
        return;
    }
    m_startFlag = true;

    std::cout << "[INFO] screen size: " << cl->width << " x " << cl->height << std::endl;
    this->resize(cl->width, cl->height);

    m_vncThread = new std::thread([this]() {
        while (m_startFlag) {
            int i = WaitForMessage(cl, 1000.0/60.0);
            if (i < 0) {
                std::cout << "[INFO] disconnected" << std::endl;
                rfbClientCleanup(cl);
                break;
            }

            if (i && !HandleRFBServerMessage(cl)) {
                std::cout << "[INFO] disconnected" << std::endl;
                rfbClientCleanup(cl);
                break;
            }
        };
    });
}


QVncViewer::~QVncViewer(){}