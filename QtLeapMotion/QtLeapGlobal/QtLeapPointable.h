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

#ifndef QTLEAPPOINTABLE_H
#define QTLEAPPOINTABLE_H

#include <QObject>
#include <QVector3D>
#include "Leap.h"
#include <QtLeapGlobal/QtLeapGlobal.h>


namespace QtLeapMotion
{

class QtLeapHand;

class QTLEAPMOTION_EXPORT QtLeapPointable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(bool hovering READ isHovering NOTIFY hoveringChanged)
    Q_PROPERTY(bool touching READ isTouching NOTIFY touchingChanged)
    Q_PROPERTY(float width READ getWidth NOTIFY widthChanged())
    Q_PROPERTY(float length READ getLength NOTIFY lengthChanged())
    Q_PROPERTY(float touchDistance READ getTouchDistance NOTIFY touchDistanceChanged)
    Q_PROPERTY(float timeVisible READ getTimeVisible NOTIFY timeVisibleChanged)
    Q_PROPERTY(QVector3D position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D direction READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(QVector3D stabilizedPosition READ getStabilizedPosition NOTIFY stabilizedPositionChanged)
    Q_PROPERTY(QVector3D velocity READ getVelocity NOTIFY velocityChanged)
    Q_PROPERTY(QVector3D tipPosition READ getTipPosition NOTIFY tipPositionChanged)
    Q_PROPERTY(QVector3D tipVelocity READ getTipVelocity NOTIFY tipVelocityChanged)
    Q_PROPERTY(QVector3D stabilizedTipPosition READ getStabilizedTipPosition NOTIFY stabilizedTipPositionChanged)
    Q_PROPERTY(QtLeapMotion::QtLeapHand *hand READ getHand CONSTANT)

public:
    QtLeapPointable(Leap::Pointable *pointable, QtLeapHand *parent);
    virtual ~QtLeapPointable();

    int getId() const;
    bool isHovering() const;
    bool isTouching() const;
    float getWidth() const;
    float getLength() const;
    float getTouchDistance() const;
    float getTimeVisible() const;

    QVector3D getPosition() const;
    QVector3D getDirection() const;
    QVector3D getStabilizedPosition() const;
    QVector3D getVelocity() const;
    QVector3D getTipPosition() const;
    QVector3D getTipVelocity() const;
    QVector3D getStabilizedTipPosition() const;

    QtLeapHand *getHand() const;

    void setHovering(bool hovering);
    void setTouching(bool touching);
    void setWidth(float width);
    void setLength(float length);
    void setTouchDistance(float touchDistance);
    void setTimeVisible(float timeVisible);
    void setPosition(const QVector3D &position);
    void setDirection(const QVector3D &direction);
    void setStabilizedPosition(const QVector3D &stabilizedPosition);
    void setVelocity(const QVector3D &velocity);
    void setTipPosition(const QVector3D &tipPosition);
    void setTipVelocity(const QVector3D &tipVelocity);
    void setTipStabilizedPosition(const QVector3D &stabilizedTipPosition);

private:

    int m_id;

    bool m_hovering;
    bool m_touching;

    float m_width;
    float m_length;
    float m_touchDistance;
    float m_timeVisible;

    QVector3D m_position;
    QVector3D m_direction;
    QVector3D m_stabilizedPosition;
    QVector3D m_velocity;
    QVector3D m_tipPosition;
    QVector3D m_tipVelocity;
    QVector3D m_stabilizedTipPosition;

    QtLeapHand * m_hand;

signals:
    void hoveringChanged();
    void touchingChanged();
    void widthChanged();
    void lengthChanged();
    void touchDistanceChanged();
    void timeVisibleChanged();
    void positionChanged();
    void directionChanged();
    void stabilizedPositionChanged();
    void velocityChanged();
    void tipPositionChanged();
    void tipVelocityChanged();
    void stabilizedTipPositionChanged();
};

}

#endif // QTLEAPPOINTABLE_H
