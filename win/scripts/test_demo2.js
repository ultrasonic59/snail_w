
var point = new Object();
point.x = 78;
point.y = 58;
var command = new Object();
    command.cmd = "Rect";
command.width = 37;
command.height = 37;
command.thick = 3;
command.brush = 2345678;
command.color = 1612378;
command.point = point;

scene.sl_obr_cmd(JSON.stringify(command));
point.x = 178;
scene.sl_obr_cmd(JSON.stringify(command));
