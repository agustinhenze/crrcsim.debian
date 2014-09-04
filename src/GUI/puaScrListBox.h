/*
 * CRRCsim - the Charles River Radio Control Club Flight Simulator Project
 *
 * Copyright (C) 2005, 2006 Jan Reucker (original author)
 * Copyright (C) 2008 Jens Wilhelm Wulf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */
  

// puaScrListBox.h - a scrolling PUI list box.
// Filename in FG sources: puList.hxx

#ifndef __PUASCRLISTBOX_H
#define __PUASCRLISTBOX_H

// Include config file generated by configure
#ifdef HAVE_CONFIG_H
#  include <crrc_config.h>
#endif

#include <plib/pu.h>


/**
 * ListBox with better readability
 *
 * PLIB 1.8.5 introduced some changes to the puListBox
 * drawing style. With CRRCsim's color scheme, the
 * selected entry in a puListBox can hardly be
 * distinguished from the unselected entries. So we
 * simply override the draw() method and adjust the
 * colors for optimized readability.
 */
class puaCRRCListBox : public puListBox
{
  public:
    puaCRRCListBox (int x, int y, int w, int h, char ** contents = NULL);
    void draw(int dx, int dy);
  
  private:
    GLfloat selectioncol[4];
};


/** \brief A scrolling list for PUI.
 * 
 *  This widget consists of a puListBox, a slider and two
 *  arrow buttons. This makes the ListBox scrollable,
 *  very handy if the box is too small to show all items
 *  at once.
 *
 *  (Original code taken from FlightGear 0.9.6 sources,
 *   modified by Jan Reucker)
 */
class puaScrListBox : public puGroup
{
  public:
    puaScrListBox (int x, int y, int w, int h);
    puaScrListBox (int x, int y, int w, int h, char ** contents);
    virtual ~puaScrListBox ();

    virtual void newList (char ** contents);

    virtual char * getStringValue ();
    virtual int    getIntegerValue ();
    virtual void   getValue (char **ps);
    virtual void   getValue (int  *i);
  
    virtual void   setValue (int i);

    virtual void   setStyle (int style);

    int  getNumItems ( void ) const ;
    int  getTopItem  ( void ) const ;
    void setTopItem  ( int item_index );


    /**
     *  Get the widget's current style.
     *  \return current style
     */
    virtual int    getStyle (void) const
    {
      return _style;
    };

  protected:
    virtual void init (int w, int h);

  private:
    char ** _contents;
    //~ puFrame * _frame;
    puListBox * _list_box;
    puSlider * _slider;
    puArrowButton * _up_arrow;
    puArrowButton * _down_arrow;
    int _style;
};

#endif // __PUASCRLISTBOX_H
