/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#ifndef LEAPGESTUREAREA_H
#define LEAPGESTUREAREA_H

#include <QQuickItem>
#include <QSGSimpleRectNode>
#include "LeapMotionServiceUserInterface.h"

namespace Tepee3DQmlExtensions
{

class LeapGesture
{
public :
    virtual int    getId() const = 0;
    virtual void   setId(int id) = 0;
};


class LeapCircleGesture : public QObject, public LeapGesture
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(bool clockwise READ getClockwise NOTIFY clockwiseChanged)
    Q_PROPERTY(QVector3D center READ getCenter NOTIFY centerChanged)
    Q_PROPERTY(QVector3D normal READ getNormal NOTIFY normalChanged)
    Q_PROPERTY(qreal radius READ getRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal turns READ getTurns NOTIFY turnsChanged)
    Q_PROPERTY(CircleGestureState state READ getState NOTIFY stateChanged)
    Q_ENUMS(CircleGestureState)

public:
    enum CircleGestureState {CircleGestureStart = 1, CircleGestureUpdated, CircleGestureDone };

private:
    int m_id;
    QVector3D m_center;
    QVector3D m_normal;
    qreal m_radius;
    qreal m_turns;
    CircleGestureState m_state;
    bool m_clockwise;

public :


    LeapCircleGesture();

    CircleGestureState getState() const;
    QVector3D getCenter() const;
    QVector3D getNormal() const;
    qreal     getRadius() const;
    qreal     getTurns() const;
    bool      getClockwise() const;
    int       getId() const;

    void      setId(int id);
    void      setClockwise(bool clockwise);
    void      setState(CircleGestureState state);
    void      setCenter(const QVector3D &center);
    void      setNormal(const QVector3D &normal);
    void      setRadius(qreal radius);
    void      setTurns(qreal turns);

signals :
    void    stateChanged();
    void    centerChanged();
    void    normalChanged();
    void    radiusChanged();
    void    turnsChanged();
    void    clockwiseChanged();
};

class LeapSwipeGesture : public QObject, public LeapGesture
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(QVector3D direction READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(QVector3D position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D startPosition READ getStartPosition NOTIFY startPositionChanged)
    Q_PROPERTY(qreal speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(SwipeGestureState state READ getState NOTIFY stateChanged)
    Q_ENUMS(SwipeGestureState)

public :
    enum SwipeGestureState {SwipeGestureStart = 1, SwipeGestureUpdated, SwipeGestureDone };

private:
    SwipeGestureState m_state;
    QVector3D m_direction;
    QVector3D m_position;
    QVector3D m_startPosition;
    qreal     m_speed;
    int       m_id;

public :


    LeapSwipeGesture();

    SwipeGestureState getState() const;
    QVector3D getDirection() const;
    QVector3D getPosition() const;
    QVector3D getStartPosition() const;
    qreal     getSpeed() const;
    int       getId() const;

    void      setId(int id);
    void      setState(SwipeGestureState state);
    void      setDirection(const QVector3D &direction);
    void      setPosition(const QVector3D &position);
    void      setStartPosition(const QVector3D &startPosition);
    void      setSpeed(qreal speed);

signals :
    void directionChanged();
    void positionChanged();
    void startPositionChanged();
    void speedChanged();
    void stateChanged();
};


class LeapTapGesture : public QObject, public LeapGesture
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(QVector3D direction READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(QVector3D position READ getPosition NOTIFY positionChanged)

private:
    int m_id;
    QVector3D m_direction;
    QVector3D m_position;

public :
    LeapTapGesture();

    int       getId() const;
    QVector3D getDirection() const;
    QVector3D getPosition() const;

    void      setId(int id);
    void      setPosition(const QVector3D position);
    void      setDirection(const QVector3D direction);

signals:
    void      directionChanged();
    void      positionChanged();
};



class LeapGestureArea : public QQuickItem, public Services::LeapMotionServiceGestureUserInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::LeapMotionServiceGestureUserInterface)
//     QQmlParserStatus interface
public:
    LeapGestureArea(QQuickItem *parent = 0);
    ~LeapGestureArea();

private :
   QHash<int, Tepee3DQmlExtensions::LeapGesture*> savedGestures;

protected :
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);
    // QQmlParserStatus interface
    void componentComplete();
    void itemChange(ItemChange, const ItemChangeData &);

    // LeapMotionServiceGestureUserInterface interface
public:
    void onCircleGestureCallBack(int gestureId,
                                 const QVector3D cicrcleCenter,
                                 const QVector3D circleNormal,
                                 const float circleRadius,
                                 const float circleTurns,
                                 const bool clockwise,
                                 const GestureState circleGestureState);
    void onScreenTapGestureCallBack(int gestureId,
                                    const QVector3D screenTapDirection,
                                    const QVector3D screenTapPosition,
                                    const GestureState screenTapGestureState);
    void onKeyTapGestureCallBack(int gestureId,
                                 const QVector3D keyTapDirection,
                                 const QVector3D keyTapPosition,
                                 const GestureState keyTapGestureState);
    void onSwipeGestureCallBack(int gestureId,
                                const QVector3D swipeDirection,
                                const QVector3D swipePosition,
                                const QVector3D swipeStartPosition,
                                const float swipeSpeed,
                                const GestureState swipeGestureState);

signals:
    void registerToLeapMotionGestures(QObject *listener);
    void unregisterFromLeapMotionGestures(QObject *listener);
    void circleGesture(LeapCircleGesture *gesture);
    void swipeGesture(LeapSwipeGesture *gesture);
    void keyTapGesture(LeapTapGesture *gesture);
    void screenTapGesture(LeapTapGesture *gesture);

};
}

#endif // LEAPGESTUREAREA_H
