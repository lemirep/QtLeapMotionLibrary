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

#ifndef QTLEAPSWIPEGESTURE_H
#define QTLEAPSWIPEGESTURE_H

#include <QtLeapGesture.h>
#include <QtLeapGlobal.h>
#include <QVector3D>
#include <QString>
#include <QObject>

namespace QtLeapMotion
{

class QtLeapSwipeGesturePrivate;

class QTLEAPMOTION_EXPORT QtLeapSwipeGesture : public QObject, public QtLeapGesture
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(QVector3D direction READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(QVector3D position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D startPosition READ getStartPosition NOTIFY startPositionChanged)
    Q_PROPERTY(qreal speed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(GestureState state READ getState NOTIFY stateChanged)
    Q_ENUMS(GestureState)

public :
    explicit QtLeapSwipeGesture(QObject *parent = 0);
    ~QtLeapSwipeGesture();

    GestureState getState() const;
    QVector3D getDirection() const;
    QVector3D getPosition() const;
    QVector3D getStartPosition() const;
    qreal     getSpeed() const;
    int       getId() const;

    void      setId(int id);
    void      setState(GestureState state);
    void      setState(Leap::Gesture::State state);
    void      setDirection(const QVector3D &direction);
    void      setPosition(const QVector3D &position);
    void      setStartPosition(const QVector3D &startPosition);
    void      setSpeed(qreal speed);
    void      update(const Leap::Gesture &gesture);
    static QtLeapSwipeGesture *fromLeapGesture(const Leap::Gesture &gesture);

signals :
    void directionChanged();
    void positionChanged();
    void startPositionChanged();
    void speedChanged();
    void stateChanged();

private:
    Q_DECLARE_PRIVATE(QtLeapSwipeGesture)
    QtLeapSwipeGesturePrivate *d_ptr;

};

} //QtLeapMotion

#endif // QTLEAPSWIPEGESTURE_H
