#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>
#include <QFileSystemWatcher>
#include <QList>

#include <memory>

#include "tasks/tasks_base.h"

#include "tasks_list.h"
#include "deshaker_configuration.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

public slots:

    void PerformScan(const QString &path);

private:

    //!
    //! \brief Function that scans directory and looks for any incomplete tasks artifacts,
    //! Then deletes the files.
    //!
    //! Do not call this function while a task is ongoing.
    //!
    void CleanIncomplete(const QString &path);

    void StartNextTasks();

    void CheckForValidVDubPath();

    void CheckForMonitoring();

    void StartMonitoring();

    void StopMonitoring();

private slots:

    void TasksFinished(TasksBase *task, ActionResult result);

    void on_btn_Browse_VDub_clicked();

    void on_btn_BrowseScanDir_clicked();

    void on_btn_StartStop_clicked();

private:

    void VDubDirProvided(const QString &dir);

    void SourceDirProvied(const QString &dir);

private:
    Ui::SettingsDialog *ui;

    QFileSystemWatcher *watcher;

    bool m_ValidVDubDir;
    bool m_CurrentlyMonitoring;
    bool m_StoppedViaButton;

    TasksList m_QueuedTasks;
    TasksList m_ActiveTasks;

    DeshakerConfiguration m_DeshakerConfiguration;
};

#endif // MAINWINDOW_H
