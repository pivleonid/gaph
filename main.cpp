#include "mainwindow.h"

#include <QApplication>

#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>

//QScopedPointer<QFile>   m_logFile;

//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    // Открываем поток записи в файл
//    QTextStream out(m_logFile.data());
//    // Записываем дату записи
//    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
//    // По типу определяем, к какому уровню относится сообщение
//    switch (type)
//    {
//    case QtInfoMsg:     out << "INF "; break;
//    case QtDebugMsg:    out << "DBG "; break;
//    case QtWarningMsg:  out << "WRN "; break;
//    case QtCriticalMsg: out << "CRT "; break;
//    case QtFatalMsg:    out << "FTL "; break;
//    }
//    // Записываем в вывод категорию сообщения и само сообщение
//    out << context.category << ": "
//        << msg << endl;
//    out.flush();    // Очищаем буферизированные данные
//}

int main(int argc, char *argv[])
{
//    // Устанавливаем файл логирования
//    m_logFile.reset(new QFile(QDir::currentPath() + "/logFile.txt"));
//    // Открываем файл логирования
//    m_logFile.data()->open(QFile::Append | QFile::Text);
//    qInstallMessageHandler(myMessageOutput);

//    QTextStream out(m_logFile.data());
//    // Записываем дату записи
//    out << QDateTime::currentDateTime().toString("--------------------------  yyyy-MM-dd hh:mm:ss.zzz --------------------------") << endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
