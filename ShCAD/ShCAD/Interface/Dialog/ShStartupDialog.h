
#ifndef _SHSTARTUPDIALOG_H
#define _SHSTARTUPDIALOG_H

#include <qdialog.h>

class QPushButton;
class QResizeEvent;
class QComboBox;
class ShStartupDialog : public QDialog {
	Q_OBJECT

private:
	QPushButton *okButton;
	QPushButton *cancelButton;
	QComboBox *languageCombo;

public:
	ShStartupDialog(QWidget *parent = nullptr);
	~ShStartupDialog();

protected:
	virtual void resizeEvent(QResizeEvent *event);


	private slots:
	void okButtonClicked();
	void cancelButtonClicked();
};

#endif //_SHSTARTUPDIALOG_H