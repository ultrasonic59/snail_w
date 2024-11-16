var win=new Dialog;
var btn=new Button(win);
var txt=new TextEdit(win);
var lbl=new Label(win);
win.setPosition(100,100,200,100);
btn.setPosition(150,40,40,25);
txt.setPosition(10,40,130,25);
lbl.setPosition(10,15,130,25);
lbl.setText("Hellow Script Window!!");

function cleckButton()
{
	txt.append("Clicked!!");
}

btn.clicked.connect(cleckButton);
btn.clicked();

print(win.exec());
