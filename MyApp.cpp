#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include <string>
#include <iostream>
using namespace std;

class MyApp : public QWidget {
    // SLOT を作る場合必須
    Q_OBJECT
public:
    MyApp(QApplication* app) { this->app = app; };
    virtual ~MyApp(void) {};
    void init(void);
public slots:
    void toggled(int id, bool status) {
        cout << "toggled id=" << id << ", status=" << status << endl;
    };
    void open();
    void slide(int value);
    void changedCB1(int state);
    void changedCB2(int state);
private:
    QButtonGroup* makeButtonGroup(QHBoxLayout* w
                                  , const char* label
                                  , const char* strs[]);

private:
    QApplication* app;
    QVBoxLayout* v;
    QHBoxLayout* h1;
    QHBoxLayout* h2;
    QHBoxLayout* h3;
    QHBoxLayout* h4;
    QHBoxLayout* h5;
    QLabel* fnameLabel;
    QLabel* sliderValueLabel;
    QSlider* slider;
    QCheckBox* cb1;
    QCheckBox* cb2;
};


void
MyApp::init(void)
{
    v = new QVBoxLayout();

    h1 = new QHBoxLayout();
    static const char* h1strs[] = {
        "B1",
        "B2",
        "B3",
        "B4",
        "B5",
        NULL,
    };
    makeButtonGroup(h1, "H1", h1strs);
    v->addLayout(h1);

    h2 = new QHBoxLayout();
    static const char* h2strs[] = {
        "B1",
        "B2",
        "B3",
        NULL,
    };
    makeButtonGroup(h2, "H2", h2strs);
    v->addLayout(h2);

    h3 = new QHBoxLayout();
    QPushButton* b = new QPushButton("Open");
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(open()));
    fnameLabel = new QLabel();
    h3->addWidget(fnameLabel);
    h3->addWidget(b);
    v->addLayout(h3);

    h4 = new QHBoxLayout();
    sliderValueLabel = new QLabel();
    h4->addWidget(sliderValueLabel);
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(10);
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slide(int)));
    h4->addWidget(slider);
    v->addLayout(h4);

    h5 = new QHBoxLayout();
    h5->addWidget(new QLabel("CheckBoxes"));
    cb1 = new QCheckBox("Option1");
    QObject::connect(cb1, SIGNAL(stateChanged(int))
                     , this, SLOT(changedCB1(int)));
    h5->addWidget(cb1);
    cb2 = new QCheckBox("Option2");
    QObject::connect(cb2, SIGNAL(stateChanged(int))
                     , this, SLOT(changedCB2(int)));
    h5->addWidget(cb2);
    v->addLayout(h5);

    setLayout(v);
}

QButtonGroup*
MyApp::makeButtonGroup(QHBoxLayout* w
                       , const char* label
                       , const char* strs[])
{
    QLabel* l = new QLabel(label);
    w->addWidget(l);
    QButtonGroup* g = new QButtonGroup();
    for (int id = 0; strs[id] != NULL; id++) {
        QRadioButton* b = new QRadioButton(strs[id]);
        w->addWidget(b);
        g->addButton(b, id);
    }
    QObject::connect(g, SIGNAL(buttonToggled(int,bool))
                     , this, SLOT(toggled(int,bool)));
    return g;
}

void
MyApp::open()
{
    QString fname = QFileDialog::getOpenFileName(this);
    if (fname.isEmpty())
        return;
    int pos = fname.lastIndexOf("/");
    if (pos >= 0) {
        fname.remove(0, pos+1);
    }
    cout << "open " << fname.toStdString() << endl;
    fnameLabel->setText(fname);
}

void
MyApp::slide(int value)
{
    sliderValueLabel->setNum(value);
}

void
MyApp::changedCB1(int state)
{
    cout << "CB1 state=" << state << endl;
}

void
MyApp::changedCB2(int state)
{
    cout << "CB2 state=" << state << endl;
}

int
main(int ac, char* av[])
{
    QApplication app(ac, av);
    MyApp* w = new MyApp(&app);
    w->init();
    w->show();
    
    return app.exec();
}

// SLOT を作る場合必須
#include "MyApp.moc"
