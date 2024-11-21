
#include "QVncViewer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    if(argc < 3) {
        std::cout << "Usage: "
                  << argv[0]
                  << " <server ip>"
                  << " <port>"
                  << "\n";
        return 1;
    }


    QVncViewer vncViewer;
    vncViewer.serverIp = std::string{argv[1]};
    vncViewer.serverPort = std::atoi(argv[2]);
    vncViewer.show();
    vncViewer.start();
    return app.exec();
}