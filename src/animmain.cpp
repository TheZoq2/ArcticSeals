
#include <QApplication>
#include <QPushButton>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    QWidget window;
    //button.setSize(100,30);
    
    QWidget* menuBar = new QWidget(&window);
    menuBar->setFixedSize(100, 1080);

    QPushButton* button = new QPushButton("Test", menuBar);
    button->setPosition(0, 25);
    QPushButton* button2 = new QPushButton("Test2", menuBar);
    QPushButton* button3 = new QPushButton("Test3", menuBar);
    QPushButton* button4 = new QPushButton("Test4", menuBar);

    window.show();

    return app.exec();
}
