#include "param_ed.h"

#include <typeinfo>

#include <QMouseEvent>
#include <QKeyEvent>
 
param_ed::param_ed(QWidget *parent) :
					QLineEdit(parent),
					i_max(0),
					i_min(0),
					i_inc_step(1),
					curr_type(-1),
					p_cdata(nullptr),
					p_sdata(nullptr),
					p_ldata(nullptr),
					p_cdata_s(nullptr),
					p_sdata_s(nullptr),
					p_ldata_s(nullptr),
					num_dig(2),
					coeff(0),
					num_dights(0),
					shift(0),
					ena_enter_on_off(false),
					ena_edit(true)
{
}

void param_ed::mouseDoubleClickEvent(QMouseEvent* pe)
{
    Q_UNUSED(pe)

	if(ena_enter_on_off)
		emit on_off();
}

void param_ed::wheelEvent(QWheelEvent *p_e)
{
	QPoint numDegrees = p_e->angleDelta() / 8;
	if(ena_edit && !numDegrees.isNull())
	{
		numDegrees /= 15;
		if(numDegrees.y() > 0)
		{
			inc_par();
			show_par();
		}
		else if(numDegrees.y() < 0)
		{
			dec_par();
			show_par();
		}
		else
			QLineEdit::wheelEvent(p_e);
	}
	else
		QLineEdit::wheelEvent(p_e);
}

void param_ed::set_min_max(int imin,int imax)
{
	i_max=imax;
	i_min=imin;
}
void param_ed::set_ena_edit(bool iena_edit)
{
	ena_edit=iena_edit;
}

void param_ed::set_inc_step(int istep)
{
	i_inc_step=istep;
}
void param_ed::set_num_dig(int inum_dig)
{
	num_dig=inum_dig;
	if(num_dights == 0)
		setMaxLength(inum_dig);
	else
		setMaxLength(inum_dig+1);
}
void param_ed::set_coeff(int icoeff)
{
	coeff=icoeff;
	if(coeff >= 10)
		{
		num_dights = log10(static_cast<float>(coeff));
		setMaxLength(num_dig+1);
		}
	else
		{
		num_dights = 0;
		setMaxLength(num_dig);
		}
}

void param_ed::set_shift(int ishift)
{
	shift = ishift;
}

void param_ed::switch_data_off()
{
	p_cdata=nullptr;
	p_sdata=nullptr;
	p_ldata=nullptr;
	p_cdata_s=nullptr;
	p_sdata_s=nullptr;
	p_ldata_s=nullptr;
}

void param_ed::set_colors(const char *col)
{
	if(strcmp("rgb(0, 0, 0)", col) == 0)
		setStyleSheet("");
	else
	{
		QString tstr;
///		tstr.sprintf("color:%s",col);
		tstr.asprintf("color:%s", col);
		setStyleSheet(tstr);
	}
}

void param_ed::set_ena_enter_on_off(bool ena)
{
	ena_enter_on_off=ena;
}

void param_ed::inc_par()
{
	bool any_type = true;

	switch(curr_type)
	{
	case 0:
		inc_par_data(p_cdata);
		break;
	case 1:
		inc_par_data(p_sdata);
		break;
	case 2:
		inc_par_data(p_ldata);
		break;
	case 3:
		inc_par_data(p_cdata_s);
		break;
	case 4:
		inc_par_data(p_sdata_s);
		break;
	case 5:
		inc_par_data(p_ldata_s);
		break;
	default:
		any_type = false;
	}
	if(any_type)
		emit param_changed();
}

void param_ed::dec_par()
{
	bool any_type = true;
	switch(curr_type)
	{
	case 0:
		dec_par_data(p_cdata);
		break;
	case 1:
		dec_par_data(p_sdata);
		break;
	case 2:
		dec_par_data(p_ldata);
		break;
	case 3:
		dec_par_data(p_cdata_s);
		break;
	case 4:
		dec_par_data(p_sdata_s);
		break;
	case 5:
		dec_par_data(p_ldata_s);
		break;
	default:
		any_type = false;
	}
if(any_type)
	emit param_changed();
}

void param_ed::show_par()
{
	QString tstr;

	switch(curr_type)
	{
	case 0:
		tstr = par_data_to_str(p_cdata);
		break;
	case 1:
		tstr = par_data_to_str(p_sdata);
		break;
	case 2:
		tstr = par_data_to_str(p_ldata);
		break;
	case 3:
		tstr = par_data_to_str(p_cdata_s);
		break;
	case 4:
		tstr = par_data_to_str(p_sdata_s);
		break;
	case 5:
		tstr = par_data_to_str(p_ldata_s);
		break;
	default:;
	}
setText(tstr);
}

void param_ed::apply_current()
{
	ApplyNewText();
	show_par();
}

void param_ed::set_new_value(const int &val)
{
	switch(curr_type)
	{
	case 0:
		*p_cdata = val;
		break;
	case 1:
		*p_sdata = val;
		break;
	case 2:
		*p_ldata = val;
		break;
	case 3:
		*p_cdata_s = val;
		break;
	case 4:
		*p_sdata_s = val;
		break;
	case 5:
		*p_ldata_s = val;
		break;
	default:;
	}
}

void param_ed::ApplyNewText()
{
	QString tstr=text();

	if(num_dights > 0)
	{
		int itmp =  tstr.toFloat() * coeff + 0.5f - shift;
		if(itmp > i_max)
			itmp = i_max;
		else if(itmp < i_min)
			itmp = i_min;
		set_new_value(itmp);
	}
	else
	{
		int itmp=tstr.toInt() - shift;

		if(itmp > i_max)
			itmp = i_max;
		else if(itmp < i_min)
			itmp = i_min;

		set_new_value(itmp);
	}
}

void param_ed::keyPressEvent(QKeyEvent * pe)
{
	switch (pe->key()) 
	{
	case Qt::Key_Up:
	case 0x42e:
	case Qt::Key_PageUp:
		if(ena_edit)
			{
			inc_par();
			show_par();
			}
		break;

	case Qt::Key_Down:
	case 0x411:
	case Qt::Key_PageDown:
		if(ena_edit)
		{
			dec_par();
			show_par();
		}
		break;
	case Qt::Key_Enter:
	case Qt::Key_Return:
        if(!ena_enter_on_off)
            ApplyNewText();
		show_par();
			if(ena_edit)
				emit param_changed();

			if(ena_enter_on_off)
				emit on_off();
		break;
	case Qt::Key_Comma:
		if(ena_edit)
		{
			QString tstr=text();
			if(num_dights != 0 && !tstr.contains('.'))
			{
				tstr+=".";
				setText(tstr);
			}
			else
			{
				dec_par();
				show_par();
			}
		}
		break;
	case Qt::Key_Period:
		if(ena_edit)
		{
			QString tstr=text();
			if(num_dights == 0 || tstr.contains('.'))
			{
				inc_par();
				show_par();
			}
			else
				QLineEdit::keyPressEvent(pe);
		}
		break;

    case Qt::Key_Escape:
        if(!ena_enter_on_off)
            show_par();
        break;
	case Qt::Key_0:
	case Qt::Key_1:
	case Qt::Key_2:
	case Qt::Key_3:
	case Qt::Key_4:
	case Qt::Key_5:
	case Qt::Key_6:
	case Qt::Key_7:
	case Qt::Key_8:
	case Qt::Key_9:
	case Qt::Key_Backspace:
	case Qt::Key_Delete:
		if(ena_edit)
		{
			QLineEdit::keyPressEvent(pe);
            if(ena_enter_on_off)
				{
                ApplyNewText();
				emit param_changed();
				}
		}
		break;
	case Qt::Key_Minus:
		if(curr_type >= 3 && curr_type <= 5)
		{
			if(ena_edit)
			{
				QString tstr=text();
				if(!tstr.contains('-'))
				{
					tstr="-"+tstr;
					setText(tstr);

					if(ena_enter_on_off)
						{
						ApplyNewText();
						emit param_changed();
						}
				}
			}
		}
		break;
	case Qt::Key_Left:
	case Qt::Key_Right:
		QLineEdit::keyPressEvent(pe);
		break;
	}
}
