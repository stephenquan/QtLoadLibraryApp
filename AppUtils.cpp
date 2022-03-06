#include "AppUtils.h"
#include <QDebug>

AppUtils::AppUtils(QObject* parent) :
    QObject(parent),
    m_error(ERROR_SUCCESS)
{
}

AppUtils::~AppUtils()
{
}

bool AppUtils::loadLibrary(const QString& fileName)
{
    setError(ERROR_SUCCESS);

    wchar_t szFileName[MAX_PATH] = { };
    fileName.toWCharArray(szFileName);
    HMODULE hModule = LoadLibraryW(szFileName);
    qDebug() << "LoadLibrary(" << szFileName << ") = " << reinterpret_cast<qint64>(hModule);

    if (hModule == NULL)
    {
        DWORD error = GetLastError();
        setError(error);
        qDebug() << "error: " << error;
        return false;
    }

    return true;
}

QString AppUtils::getEnv(const QString& var)
{
    return QString::fromUtf8(qgetenv(var.toUtf8().data()));
}

void AppUtils::putEnv(const QString& var, const QString& value)
{
    qputenv(var.toUtf8().data(), value.toUtf8().data());
}

void AppUtils::setError(DWORD error)
{
    if (m_error == error)
    {
        return;
    }

    m_error = error;

    emit errorChanged();
}

#include "AppUtils.moc"
