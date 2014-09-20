/****************************************************************************
**
** Copyright (C) Paul Lemire
** Contact: paul.lemire@epitech.eu
**
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

#ifndef __LEAPHAND_H__
#define __LEAPHAND_H__

#include <QObject>
#include <QVector3D>
#include <QList>
#include <QtLeapGlobal.h>

namespace Leap
{
class Hand;
}

namespace QtLeapMotion
{

class QtLeapPointable;
class QtLeapFinger;
class QtLeapTool;
class QtLeapHandPrivate;

class QTLEAPMOTION_EXPORT QtLeapHand : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(float pitch READ getPitch NOTIFY pitchChanged)
    Q_PROPERTY(float yaw READ getYaw NOTIFY yawChanged)
    Q_PROPERTY(float roll READ getRoll NOTIFY rollChanged)
    Q_PROPERTY(float timeVisible READ getTimeVisible NOTIFY timeVisibleChanged)
    Q_PROPERTY(float sphereRadius READ getSphereRadius NOTIFY sphereRadiusChanged)
    Q_PROPERTY(QVector3D direction READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(QVector3D position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D normal READ getNormal NOTIFY normalChanged)
    Q_PROPERTY(QVector3D velocity READ getVelocity NOTIFY velocityChanged)
    Q_PROPERTY(QVector3D stabilizedPosition READ getStabilizedPosition NOTIFY stabilizedPositionChanged)
    Q_PROPERTY(QVector3D sphereCenter READ getSphereCenter NOTIFY sphereCenterChanged)
    Q_PROPERTY(QList<QtLeapMotion::QtLeapPointable *> pointables READ getPointables)
    Q_PROPERTY(QList<QtLeapMotion::QtLeapFinger *> fingers READ getFingers)
    Q_PROPERTY(QList<QtLeapMotion::QtLeapTool *> tools READ getTools)
    Q_PROPERTY(bool isFist READ isFist NOTIFY isFistChanged)
    Q_PROPERTY(bool isLeft READ isLeft NOTIFY isLeftChanged)
    Q_PROPERTY(bool isRight READ isRight NOTIFY isRightChanged)

public :
    QtLeapHand(QObject *parent = 0);
    ~QtLeapHand();

    static QtLeapHand* fromLeapHand(Leap::Hand *hand);
    void update(Leap::Hand *hand);

    int   getId() const;
    float getPitch() const;
    float getYaw() const;
    float getRoll() const;
    float getTimeVisible() const;
    float getSphereRadius() const;
    bool isLeft() const;
    bool isRight() const;
    bool isFist() const;

    QVector3D getDirection() const;
    QVector3D getPosition() const;
    QVector3D getNormal() const;
    QVector3D getVelocity() const;
    QVector3D getStabilizedPosition() const;
    QVector3D getSphereCenter() const;

    QList<QtLeapPointable*> getPointables() const;
    QList<QtLeapFinger*> getFingers() const;
    QList<QtLeapTool*> getTools() const;

    Leap::Hand*  getHand() const;

    void setId(int id);
    void setPitch(float pitch);
    void setYaw(float yaw);
    void setRoll(float roll);
    void setLeft(bool left);
    void setRight(bool right);
    void setTimeVisible(float timeVisible);
    void setSphereRadius(float sphereRadius);
    void setDirection(const QVector3D &direction);
    void setPosition(const QVector3D &position);
    void setNormal(const QVector3D &normal);
    void setVelocity(const QVector3D &velocity);
    void setStabilizedPosition(const QVector3D &stabilizedPosition);
    void setSphereCenter(const QVector3D &sphereCenter);
    void setFist(bool fist);

signals:
    void pitchChanged();
    void yawChanged();
    void rollChanged();
    void timeVisibleChanged();
    void sphereRadiusChanged();
    void directionChanged();
    void positionChanged();
    void normalChanged();
    void velocityChanged();
    void stabilizedPositionChanged();
    void sphereCenterChanged();
    void isLeftChanged();
    void isRightChanged();
    void isFistChanged();

private :
    Q_DECLARE_PRIVATE(QtLeapHand)
    QtLeapHandPrivate *d_ptr;
};

}

#endif // __LEAPHAND_H__
