
#include <QGuiApplication>
#include <QScopedPointer>
#include "LeapMotionQQuickView.h"

int     main(int ac, char **av)
{
    QScopedPointer<QGuiApplication> app(new QGuiApplication(ac, av));
    LeapMotionQQuickView *view = new LeapMotionQQuickView();

    view->showView();
    return app->exec();
}
