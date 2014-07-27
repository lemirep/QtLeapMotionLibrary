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

#ifndef QTLEAPCIRCLEGESTURE_H
#define QTLEAPCIRCLEGESTURE_H

#include <QObject>
#include <QVector3D>
#include <QtLeapGesture.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QtLeapCircleGesturePrivate;

class QTLEAPMOTION_EXPORT QtLeapCircleGesture : public QObject, public QtLeapGesture
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(bool clockwise READ getClockwise NOTIFY clockwiseChanged)
    Q_PROPERTY(QVector3D center READ getCenter NOTIFY centerChanged)
    Q_PROPERTY(QVector3D normal READ getNormal NOTIFY normalChanged)
    Q_PROPERTY(qreal radius READ getRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal turns READ getTurns NOTIFY turnsChanged)
    Q_PROPERTY(GestureState state READ getState NOTIFY stateChanged)
    Q_ENUMS(GestureState)

public :
    explicit QtLeapCircleGesture(QObject *parent = 0);
    ~QtLeapCircleGesture();

    GestureState getState() const;
    QVector3D getCenter() const;
    QVector3D getNormal() const;
    qreal     getRadius() const;
    qreal     getTurns() const;
    bool      getClockwise() const;
    int       getId() const;

    void      setId(int id);
    void      setClockwise(bool clockwise);
    void      setState(GestureState state);
    void      setState(Leap::Gesture::State state);
    void      setCenter(const QVector3D &center);
    void      setNormal(const QVector3D &normal);
    void      setRadius(qreal radius);
    void      setTurns(qreal turns);

    static QtLeapCircleGesture *fromLeapGesture(const Leap::Gesture &gesture);
    void      update(const Leap::Gesture &gesture);

signals :
    void    stateChanged();
    void    centerChanged();
    void    normalChanged();
    void    radiusChanged();
    void    turnsChanged();
    void    clockwiseChanged();

private:
    Q_DECLARE_PRIVATE(QtLeapCircleGesture)
    QtLeapCircleGesturePrivate *d_ptr;
};

}
#endif // QTLEAPCIRCLEGESTURE_H
