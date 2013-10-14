#ifndef __LEAPMOTIONQQUICKVIEW_H_
#define __LEAPMOTIONQQUICKVIEW_H_

#include <QQuickView>
#include "LeapMotionServiceUserInterface.h"
#include "LeapMotionController.h"

class LeapMotionQQuickView : public QQuickView,
                             public Services::LeapMotionServiceInputUserInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::LeapMotionServiceInputUserInterface)

private:
     LeapMotionController *leapController;

public :
    LeapMotionQQuickView();
    ~LeapMotionQQuickView();
    void showView();


    // LeapMotionServiceInputUserInterface interface
signals :
    void    registerToLeapMotionInputs(QObject *listener);
    void    unregisterFromLeapMotionInputs(QObject *listener);

    // Needed to connect QQuickItems to the LeapMotionController
    void    registerQQuickItemToLeapMotionGesturesInput(QObject *);
    void    unregisterQQuickItemFromLeapMotionGesturesInput(QObject *);

};

#endif // __LEAPMOTIONQQUICKVIEW_H_
