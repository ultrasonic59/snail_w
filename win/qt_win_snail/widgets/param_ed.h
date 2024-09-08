#ifndef _PARAM_ED_H_
#define _PARAM_ED_H_
 
#include <QLineEdit>


class param_ed: public QLineEdit
{
    Q_OBJECT
public:
    param_ed(QWidget *parent=0);
protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* pe) override;
	virtual void keyPressEvent(QKeyEvent * pe) override;
	virtual void wheelEvent(QWheelEvent * pe) override;
	int i_max;
	int i_min;
	int i_inc_step;
	char curr_type;
	unsigned char	*p_cdata;
	unsigned short	*p_sdata;
	unsigned long	*p_ldata;
	signed char		*p_cdata_s;
	signed short	*p_sdata_s;
	signed long		*p_ldata_s;
	int num_dig;
	int coeff;
	int num_dights;
	int shift;
	bool ena_enter_on_off;
	bool ena_edit;
	inline void ApplyNewText();
	void switch_data_off();
	template<typename val_type> void inc_par_data(val_type *p_data);
	template<typename val_type> void dec_par_data(val_type *p_data);
	template<typename val_type> QString par_data_to_str(val_type *p_data);
	void set_new_value(const int &val);
public:
	void set_ena_edit(bool iena_edit);
	void inc_par();
	void dec_par();
	void set_ena_enter_on_off(bool ena);
	void set_min_max(int i_min,int i_max);
	void set_inc_step(int istep);
	void set_num_dig(int inum_dig);
	void set_coeff(int icoeff);
	template<typename val_type> void set_data(val_type *p_data);
	void set_colors(const char *col);
	void show_par();
	void set_shift(int);
	void apply_current();
signals:
	void on_off();
	void param_changed();
};

template<typename T, typename U> struct TypesAreEqual
{
	static const bool value = false;
};

template<typename T> struct TypesAreEqual<T,T>
{
	static const bool value = true;
};

template<typename val_type> void param_ed::set_data(val_type *p_data)
{
	switch_data_off();

	if(p_data == nullptr)
		curr_type = -1;
	else if(TypesAreEqual<val_type, unsigned char>::value)
	{
		p_cdata=reinterpret_cast<unsigned char *>(p_data);
		curr_type = 0;
	}
	else if(TypesAreEqual<val_type, unsigned short>::value)
	{
		p_sdata=reinterpret_cast<unsigned short *>(p_data);
		curr_type = 1;
	}
	else if(TypesAreEqual<val_type, unsigned long>::value)
	{
		p_ldata=reinterpret_cast<unsigned long *>(p_data);
		curr_type = 2;
	}
	else if(TypesAreEqual<val_type, signed char>::value)
	{
		p_cdata_s=reinterpret_cast<signed char *>(p_data);
		curr_type = 3;
	}
	else if(TypesAreEqual<val_type, signed short>::value)
	{
		p_sdata_s=reinterpret_cast<signed short *>(p_data);
		curr_type = 4;
	}
	else if(TypesAreEqual<val_type, signed long>::value)
	{
		p_ldata_s=reinterpret_cast<signed long *>(p_data);
		curr_type = 5;
	}
	else
		curr_type = -1;
}

template<typename val_type> void param_ed::inc_par_data(val_type *p_data)
{
    if((static_cast<int>(*p_data) + i_inc_step)<=i_max)
		*p_data += i_inc_step;
	else
		*p_data=i_max;
}

template<typename val_type> void param_ed::dec_par_data(val_type *p_data)
{
    if((static_cast<int>(*p_data) - i_inc_step)>=i_max)
		*p_data = i_max;
    else if((static_cast<int>(*p_data) - i_inc_step)>=i_min)
		*p_data -= i_inc_step;
	else
		*p_data=i_min;
}

template<typename val_type> QString param_ed::par_data_to_str(val_type *p_data)
{
	if(num_dights > 0)
			return QString::number((static_cast<float>(*p_data + shift) / coeff),'f', num_dights);

	return QString::number(*p_data + shift, 10);
}
 
#endif // _PARAM_ED_H_
