#include "settingsDialog.h"
#include "ui_settingsDialog.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>

#include "tasks/deshaker_pass1.h"
#include "tasks/deshaker_pass2.h"
#include "tasks/mpeg_conversion.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsDialog),
    m_ValidVDubDir(false),
    m_CurrentlyMonitoring(false),
    m_StoppedViaButton(false)
{
    ui->setupUi(this);

    watcher = new QFileSystemWatcher(this);

    m_DeshakerConfiguration.WriteScripts();

    VDubDirProvided("M:\\VirutalDub");
    SourceDirProvied("M:\\Videos\\Test");
}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::PerformScan(const QString &path)
{
    if(m_ValidVDubDir == false && m_CurrentlyMonitoring == true) {
        return;
    }

    QStringList files = QDir(path).entryList(QDir::NoDotAndDotDot | QDir::Files);

    QDirIterator it(path, QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QString filename = it.fileName();

        if(filename.endsWith("_stabalized.avi")) {
            if(files.contains(it.fileInfo().completeBaseName() + ".mp4") == false) {
                if(m_ActiveTasks.ShouldIgnore(it.fileInfo().absoluteFilePath()) == false && m_QueuedTasks.ShouldIgnore(it.fileInfo().absoluteFilePath()) == false)
                {
                    auto newTasks = std::make_shared<MPEGConversion>(ui->le_VDub->text(), it.fileInfo().absoluteFilePath());
                    this->m_QueuedTasks.Append(newTasks);
                }
            }
            else {
                //remove everything (should be done when mp4 conversion finishes).
            }
        }
        else if(filename.endsWith(".log")) {
            if(files.contains(it.fileInfo().completeBaseName() + "_stabalized.avi") == false) {

                if(m_ActiveTasks.ShouldIgnore(it.fileInfo().absoluteFilePath()) == false && m_QueuedTasks.ShouldIgnore(it.fileInfo().absoluteFilePath()) == false)
                {
                    QString videoFile = it.fileInfo().absoluteDir().absolutePath() + QDir::separator() + it.fileInfo().completeBaseName();
                    if(QFile::exists(videoFile + ".mp4")) {
                        videoFile += ".mp4";
                    }
                    else if(QFile::exists(videoFile + ".MP4")) {
                        videoFile += ".MP4";
                    }
                    else {
                        throw std::runtime_error("Unknown");
                    }
                    auto newTasks = std::make_shared<DeshakerPass2>(ui->le_VDub->text(), videoFile);
                    this->m_QueuedTasks.Append(newTasks);
                }
            }
            else {
                //remove .log file (should of been done when avi was compleated)
            }
        }
        else if((filename.endsWith(".mp4") && filename.endsWith("_stabalized.mp4") == false) || (filename.endsWith(".MP4") && filename.endsWith("_stabalized.MP4") == false) ) {
            if(files.contains(it.fileInfo().completeBaseName() + ".log") == false && files.contains(it.fileInfo().completeBaseName() + "_stabalized." + it.fileInfo().completeSuffix()) == false) {
                auto newTasks = std::make_shared<DeshakerPass1>(ui->le_VDub->text(), it.fileInfo().absoluteFilePath());
                this->m_QueuedTasks.Append(newTasks);
            }
        }
    }


    //if not doing an active tasks, go ahead and start one
    if(m_ActiveTasks.Size() == 0) {
        StartNextTasks();
    }
}


//!
//! \brief Function that scans directory and looks for any incomplete tasks artifacts,
//! Then deletes the files.
//!
//! Do not call this function while a task is ongoing.
//!
void SettingsDialog::CleanIncomplete(const QString &path)
{
    QStringList files = QDir(path).entryList(QDir::NoDotAndDotDot | QDir::Files);


        foreach (QString file, files) {

            if(file.at(0) == ".") {
                continue;
            }

            //If final stabalized file exists and so does the output from pass two
            //Then the final conversion wasn't complete
            //Remove final from directory and take out both files of files-to-consider
            if(file.contains("_stabalized.mp4")) {
                QString previousFile = file;
                previousFile.replace("_stabalized.mp4", "_stabalized.avi");
                if(files.contains(previousFile)) {
                    QFile::remove(path + QDir::separator() + file);
                }
            }

            if(file.contains("_stabalized.avi")) {
                QString base = file;
                base.replace("_stabalized.avi", "");

                QString P2CompleteFile = "." + base + "_p2";

                if(files.contains(P2CompleteFile) == false) {
                    QFile::remove(path + QDir::separator() + file);
                }
            }

            if(file.contains(".log")) {
                QString base = file;
                base.replace(".log", "");

                QString P1CompleteFile = "." + base + "_p1";

                if(files.contains(P1CompleteFile) == false) {
                    QFile::remove(path + QDir::separator() + file);
                }
            }
        }

}


void SettingsDialog::StartNextTasks()
{
    if(this->m_QueuedTasks.Size() == 0) {
        return;
    }
    if(this->m_ActiveTasks.Size() > 0) {
        throw std::runtime_error("Ongoing Tasks, Only one allowed at time");
    }

    std::shared_ptr<TasksBase> task = m_QueuedTasks.Pop();

    this->m_ActiveTasks.Append(task);
    connect(task.get(), SIGNAL(Done(TasksBase *, ActionResult)), this, SLOT(TasksFinished(TasksBase *, ActionResult)));
    task->Execute();
}

void SettingsDialog::CheckForValidVDubPath()
{
    QString path = ui->le_VDub->text();

    QFileInfo check_file(path + QDir::separator() + "vdub.exe");
    if(check_file.exists() && check_file.isFile()) {
        m_ValidVDubDir = true;
        ui->le_VDub->setStyleSheet("background:#ffffff;");
        CheckForMonitoring();
    }
    else {
        m_ValidVDubDir = false;
        ui->le_VDub->setStyleSheet("background:#ff0000;");
    }
}

void SettingsDialog::CheckForMonitoring() {

    QString sourceDirStr = ui->le_ScanDir->text();

    if(sourceDirStr != "") {
        QDir sourceDir(ui->le_ScanDir->text());

        if(sourceDir.exists() && m_CurrentlyMonitoring == false && m_ValidVDubDir == true) {
            m_CurrentlyMonitoring = true;
            ui->btn_StartStop->setEnabled(true);
            StartMonitoring();
            return;
        }
    }

    ui->btn_StartStop->setEnabled(false);
}

void SettingsDialog::StartMonitoring()
{
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(PerformScan(QString)));
    CleanIncomplete(ui->le_ScanDir->text());
    PerformScan(ui->le_ScanDir->text());
}

void SettingsDialog::StopMonitoring()
{
    this->m_QueuedTasks.Clear();
    this->m_ActiveTasks.Clear();
    disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(PerformScan(QString)));
}


void SettingsDialog::TasksFinished(TasksBase* task, ActionResult result)
{
    //if task failed, retry. Otherwise advance to next task.
    if(result.IsSuccess() == false) {
        auto tasksToRedo = this->m_ActiveTasks.getSharedPtr(task);
        this->m_QueuedTasks.Append(tasksToRedo);
    }
    else {
        if(task->Type() == TasksBase::DESHAKER_PASS1) {

            //make file to mark completion
            QString file(((DeshakerPass1*)task)->Filename());
            QFileInfo info(file);
            QFile completionIndicator(info.absoluteDir().absolutePath() + QDir::separator() + "."+ info.completeBaseName() + "_p1");
            completionIndicator.open(QIODevice::WriteOnly);

            auto newTasks = std::make_shared<DeshakerPass2>(ui->le_VDub->text(), ((DeshakerPass1*)task)->Filename());
            this->m_QueuedTasks.Append(newTasks);
        }
        if(task->Type() == TasksBase::DESHAKER_PASS2) {
            //make file to mark completion
            QString file(((DeshakerPass1*)task)->Filename());
            QFileInfo info(file);
            QFile completionIndicator(info.absoluteDir().absolutePath() + QDir::separator() + "."+ info.completeBaseName().remove("_stabalized") + "_p2");
            completionIndicator.open(QIODevice::WriteOnly);

            auto newTasks = std::make_shared<MPEGConversion>(ui->le_VDub->text(), task->Output());
            this->m_QueuedTasks.Append(newTasks);
        }
        if(task->Type() == TasksBase::MPEG_CONVERSION) {
            QString aviStabalized = ((MPEGConversion*)task)->Filename();
            QFileInfo info(aviStabalized);
            QString path = info.absoluteDir().absolutePath();
            QString baseName = info.completeBaseName();
            baseName.replace("_stabalized", "");

            QString P1Complete = path + QDir::separator() + "." + baseName + "_p1";
            QString P2Complete = path + QDir::separator() + "." + baseName + "_p2";
            QString logFile = path + QDir::separator() + baseName + ".log";
            QString original1 = path + QDir::separator() + baseName + ".mp4";
            QString original2 = path + QDir::separator() + baseName +  ".MP4";
            QFile::remove(P1Complete);
            QFile::remove(P2Complete);
            QFile::remove(aviStabalized);
            QFile::remove(logFile);
            //QFile.remove(original1);
            //QFile.remove(original2);
        }
    }

    m_ActiveTasks.Remove(task);

    //if not doing an active tasks, go ahead and start one
    if(m_ActiveTasks.Size() == 0) {
        StartNextTasks();
    }
}






void SettingsDialog::on_btn_Browse_VDub_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::DontResolveSymlinks);

    if(dir == "") {
        return;
    }
    else {
        VDubDirProvided(dir);
    }
}

void SettingsDialog::on_btn_BrowseScanDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::DontResolveSymlinks);

    if(dir == "") {
        return;
    }
    else {
        SourceDirProvied(dir);

    }
}

void SettingsDialog::VDubDirProvided(const QString &dir)
{
    ui->le_VDub->setText(dir);
    CheckForValidVDubPath();
}

void SettingsDialog::SourceDirProvied(const QString &dir)
{
    ui->le_ScanDir->setText(dir);
    watcher->addPath(dir);
    CheckForMonitoring();
}

void SettingsDialog::on_btn_StartStop_clicked()
{
    if(m_StoppedViaButton == false) {
        ui->btn_StartStop->setText("Start");
        StopMonitoring();
    }
    else {
        ui->btn_StartStop->setText("Stop");
        StartMonitoring();
    }
}
