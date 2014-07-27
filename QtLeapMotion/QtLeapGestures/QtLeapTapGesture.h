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

#ifndef QTLEAPTAPGESTURE_H
#define QTLEAPTAPGESTURE_H

#include <Leap.h>
#include <QObject>
#include <QVector3D>
#include <QtLeapGesture.h>
#include <QtLeapGlobal.h>

namespace QtLeapMotion
{

class QtLeapTapGesturePrivate;

class QTLEAPMOTION_EXPORT QtLeapTapGesture : public QObject, public QtLeapGesture
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(QVector3D direction READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(QVector3D position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(GestureState state READ getState NOTIFY stateChanged)
    Q_ENUMS(GestureState)

public :
    QtLeapTapGesture(QObject *parent = 0);
    virtual ~QtLeapTapGesture();

    int       getId() const;
    QVector3D getDirection() const;
    QVector3D getPosition() const;
    GestureState getState() const;

    void      setId(int id);
    void      setPosition(const QVector3D position);
    void      setDirection(const QVector3D direction);
    void      setState(QtLeapTapGesture::GestureState state);
    void      setState(Leap::Gesture::State state);

    virtual void      update(const Leap::Gesture &gesture) = 0;

signals:
    void      directionChanged();
    void      positionChanged();
    void      stateChanged();

private:
    Q_DECLARE_PRIVATE(QtLeapTapGesture)
    QtLeapTapGesturePrivate *d_ptr;
};

}

#endif // QTLEAPTAPGESTURE_H
