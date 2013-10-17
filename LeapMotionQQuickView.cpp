#include <QCoreApplication>
#include "LeapMotionQQuickView.h"
#include "LeapGestureArea.h"
#include "LeapMotionController.h"

LeapMotionQQuickView::LeapMotionQQuickView() : QQuickView()
{
     this->leapController = LeapMotionController::getInstance();

     // REGISTER OUR VIEW TO THE LEAP MOTION CONTROLLER
     QObject::connect(this, SIGNAL(registerToLeapMotionInputs(QObject*)),
                      this->leapController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
     QObject::connect(this, SIGNAL(unregisterFromLeapMotionInputs(QObject*)),
                      this->leapController, SLOT(unregisterTargetListenerFromLeapMotionInputs(QObject*)));
     QObject::connect(this, SIGNAL(registerQQuickItemToLeapMotionGesturesInput(QObject *)),
                      leapController, SLOT(registerTargetListenerToLeapMotionGestures(QObject*)));
     QObject::connect(this, SIGNAL(unregisterQQuickItemFromLeapMotionGesturesInput(QObject *)),
                      leapController, SLOT(unregisterTargetListenerFromLeapMotionGestures(QObject*)));

    // REGISTER CUSTOM QML TYPES
    qmlRegisterType<Tepee3DQmlExtensions::LeapGestureArea>("Tepee3D", 1, 0, "LeapGestureArea");
    qmlRegisterType<Tepee3DQmlExtensions::LeapCircleGesture>("Tepee3D", 1, 0, "LeapCircleGesture");
    qmlRegisterType<Tepee3DQmlExtensions::LeapSwipeGesture>("Tepee3D", 1, 0, "LeapSwipeGesture");
    qmlRegisterType<Tepee3DQmlExtensions::LeapTapGesture>("Tepee3D", 1, 0, "LeapTapGesture");

    this->setSource(QUrl("qrc:/qml/main.qml"));
}

LeapMotionQQuickView::~LeapMotionQQuickView()
{
    emit unregisterFromLeapMotionInputs(this);
    // REGISTER OUR VIEW TO THE LEAP MOTION CONTROLLER
    QObject::disconnect(this, SIGNAL(registerToLeapMotionInputs(QObject*)),
                     this->leapController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
    QObject::disconnect(this, SIGNAL(unregisterFromLeapMotionInputs(QObject*)),
                     this->leapController, SLOT(unregisterTargetListenerFromLeapMotionInputs(QObject*)));
    QObject::disconnect(this, SIGNAL(registerQQuickItemToLeapMotionGesturesInput(QObject *)),
                     leapController, SLOT(registerTargetListenerToLeapMotionGestures(QObject*)));
    QObject::disconnect(this, SIGNAL(unregisterQQuickItemFromLeapMotionGesturesInput(QObject *)),
                     leapController, SLOT(unregisterTargetListenerFromLeapMotionGestures(QObject*)));

    delete this->leapController;
}

void LeapMotionQQuickView::showView()
{
    emit registerToLeapMotionInputs(this);
    this->show();
}
