#ifndef AppUtils_H
#define AppUtils_H

#include <QObject>
#include <qt_windows.h>

class AppUtils : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int error READ error NOTIFY errorChanged);

public:
    AppUtils(QObject* parent = nullptr);
    virtual ~AppUtils();

    Q_INVOKABLE bool loadLibrary(const QString& fileName);
    Q_INVOKABLE QString getEnv(const QString& var);
    Q_INVOKABLE void putEnv(const QString& var, const QString& value);

signals:
    void errorChanged();

protected:
    DWORD m_error;

    int error() const { return static_cast<int>(m_error); }
    void setError(DWORD error);

};

#endif
