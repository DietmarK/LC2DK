/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/

/* kopie von rs_dimlinear.h , mit aenderungen */

#ifndef RS_DIMORDINATE_H
#define RS_DIMORDINATE_H

#include "rs_dimension.h"

/**
 * Holds the data that defines a ordinate dimension entity.
 */
class RS_DimOrdinateData {
public:
    /**
     * Default constructor. Leaves the data object uninitialized.
     */
    RS_DimOrdinateData() {}

    /**
     * Constructor with initialisation.
     *
     * @para 
     * @para 
     * @para 
     */
    RS_DimOrdinateData(const RS_Vector& OriginPoint,
                     const RS_Vector& FirstLine,
                     const RS_Vector& SecondLine,
		       bool is_x_type)
    {
        this->OriginPoint = OriginPoint;
        this->FirstLine = FirstLine;
        this->SecondLine = SecondLine;
      this->is_x_type = is_x_type;
    }

    friend class RS_DimOrdinate;
    friend class RS_ActionDimOrdinate;

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_DimOrdinateData& dd) {
        os << "(" << dd.FirstLine << "/" << dd.SecondLine << ")";
        return os;
    }

public:
    /** Origin point.    */
    RS_Vector OriginPoint;
    /**  */
    RS_Vector FirstLine;
    /**  */
   RS_Vector SecondLine;
   
   bool is_x_type;
};



/**
 * Class for ordinate dimension entities.
 *
 * @author Andrew Mustun , DK
 */
class RS_DimOrdinate : public RS_Dimension {
public:
    RS_DimOrdinate(RS_EntityContainer* parent,
                 const RS_DimensionData& d,
                 const RS_DimOrdinateData& ed);
    virtual ~RS_DimOrdinate() {}

    virtual RS_Entity* clone() {
        RS_DimOrdinate* d = new RS_DimOrdinate(*this);
        d->setOwner(isOwner());
        d->initId();
        d->detach();
        return d;
    }

    /**	@return RS2::EntityDimOrdinate */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityDimOrdinate;
    }

    /**
     * @return Copy of data that defines the linear dimension.
     * @see getData()
     */
    RS_DimOrdinateData getEData() const {
        return edata;
    }

    virtual RS_VectorSolutions getRefPoints();

    virtual QString getMeasuredLabel();

    virtual void update(bool autoText=false);

    RS_Vector getOriginPoint() {
        return edata.OriginPoint;
    }

    RS_Vector getFirstLine() {
        return edata.FirstLine;
    }

    RS_Vector getSecondLine() {
        return edata.SecondLine;
    }

   bool getXType() { return edata.is_x_type;}
   
   void setXType(bool b) {edata.is_x_type = b;}

    virtual void move(const RS_Vector& offset);
    virtual void rotate(const RS_Vector& center, const double& angle);
    virtual void rotate(const RS_Vector& center, const RS_Vector& angleVector);
    virtual void scale(const RS_Vector& center, const RS_Vector& factor);
    virtual void mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2);
    virtual bool hasEndpointsWithinWindow(const RS_Vector& v1, const RS_Vector& v2);
    virtual void stretch(const RS_Vector& firstCorner,
                         const RS_Vector& secondCorner,
                         const RS_Vector& offset);
    virtual void moveRef(const RS_Vector& ref, const RS_Vector& offset);

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_DimOrdinate& d);

protected:
    /** Extended data. */
    RS_DimOrdinateData edata;
   
   double SecondLineLength;
   double ConnectingLineLength;
};

#endif
