#ifndef ACTION_RESULT_H
#define ACTION_RESULT_H

#include <QString>

struct ActionResult
{
    ActionResult():
        success(true)
    {

    }

    ActionResult(const QString &error) :
        success(false),
        error(error)
    {

    }

    bool IsSuccess() const {
        return success;
    }

    QString Error() const {
        if(success == true) {
            throw std::runtime_error("Not a failure");
        }
        else {
            return error;
        }
    }

private:

    bool success;
    QString error;
};

#endif // ACTION_RESULT_H
