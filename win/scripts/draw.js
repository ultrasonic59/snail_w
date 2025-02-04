const colors = {
  BLACK: "ff000000",
  PINK: "ffaaaa00",
  RED: "ffff0000",
};

const DEFAULT_STROKE_WIDTH = 2;
const DEFAULT_STROKE_COLOR = colors.BLACK;

const commands = {
  CIRCLE: "Circle",
  RECTANGLE: "Rect",
  LINE: "Line",
};

const defaultStyle = style(colors.BLACK, colors.BLACK);

const strokeOnlyDefaultStyle = style(null, colors.BLACK);

// Для упрощения передачи координат и размеров в функции
function vec2(x, y) {
  return { x, y };
}

// Для упрощения задания стиля
// fillColor - цвет заливки
// strokeColor - цвет обводки
// strokeWidth - ширина обводки
// Если fillColor не задан, то фигура не заливается
// Если strokeColor не задан, то обводка не рисуется
// Если strokeWidth не задан, то ширина обводки равна DEFAULT_STROKE_WIDTH
function style(fillColor, strokeColor, strokeWidth = DEFAULT_STROKE_WIDTH) {
  let style = {};
  if (fillColor) {
    style.brush = {
      color: fillColor,
      style: 1,
    };
  }
  if (strokeColor) {
    style.pen = {
      color: strokeColor,
      width: strokeWidth,
    };
  }
  return style;
}

// Функция для создания эллипса
// centerVec2 - координаты центра эллипса
// sizeVec2 - размеры эллипса по осям x и y
// style - стиль, см. функцию style
// Если style не задан, то используется defaultStyle
function ellipse(centerVec2, sizeVec2, style = defaultStyle) {
  return {
    type: commands.CIRCLE,
    pos: centerVec2,
    width: sizeVec2.x,
    height: sizeVec2.y,
    // Добавляем стиль используя spread оператор
    // Пример использования spread оператора:
    // let a = { x: 1, y: 2 };
    // let b = { ...a, z: 3 };
    // console.log(b); // { x: 1, y: 2, z: 3 }
    // Функция style уже возвращает объект, в нужном формате
    // Поэтому его можно добавить к остальным полям используя spread оператор
    ...style,
  };
}

// Функция для создания круга
// centerVec2 - координаты центра круга
// radius - радиус круга
// style - стиль, см. функцию style
function circle(centerVec2, radius, style = defaultStyle) {
  return ellipse(centerVec2, vec2(radius, radius), style);
}

// Функция для создания прямоугольника
// topLeftVec2 - координаты верхнего левого угла прямоугольника
// sizeVec2 - размеры прямоугольника по осям x и y
// style - стиль, см. функцию style
function rectangle(topLeftVec2, sizeVec2, style = defaultStyle) {
  return {
    type: commands.RECTANGLE,
    pos: topLeftVec2,
    width: sizeVec2.x,
    height: sizeVec2.y,
    ...style,
  };
}

// Функция для создания линии
// startVec2 - координаты начала линии
// endVec2 - координаты конца линии
function line(startVec2, endVec2, style = strokeOnlyDefaultStyle) {
  return {
    type: commands.LINE,
    p1: startVec2,
    p2: endVec2,
    ...style,
  };
}

// Функция для перемещения фигуры
// element - фигура
// shiftVec2 - вектор смещения
// Возвращает новую фигуру с измененными координатами
function move(element, shiftVec2) {
  if (Array.isArray(element)) {
    return element.map((el) => move(el, shiftVec2));
  }
  if (element.type === commands.LINE) {
    return {
      ...element,
      p1: vec2(element.p1.x + shiftVec2.x, element.p1.y + shiftVec2.y),
      p2: vec2(element.p2.x + shiftVec2.x, element.p2.y + shiftVec2.y),
    };
  } else {
    return {
      ...element,
      pos: vec2(element.pos.x + shiftVec2.x, element.pos.y + shiftVec2.y),
    };
  }
}

// Функция для создания копии фигуры
// element - фигура
// numCopies - количество копий
// shiftVec2 - вектор смещения между копиями
function clone(element, numCopies, shiftVec2) {
  let elements = [];
  for (let i = 0; i < numCopies; i++) {
    elements.push(move(element, vec2(shiftVec2.x * i, shiftVec2.y * i)));
  }
  return elements;
}

// Функция для создания копий нескольких фигур
// elements - массив фигур
// numCopies - количество копий
// shiftVec2 - вектор смещения между копиями
// Возвращает массив новых фигур
function cloneMany(elements, numCopies, shiftVec2) {
  let newElements = [];
  for (let element of elements) {
    newElements.push(...clone(element, numCopies, shiftVec2));
  }
  return newElements;
}
// Функция для преобразования массива фигур в JSON
// elements - массив фигур
// pretty - если true, то JSON будет отформатирован с отступами в 2 пробела (для человеческого восприятия)
function toJson(elements, addObj = false, pretty = false) {
  // flatMap - метод, которая применяет функцию к каждому элементу массива
  // и объединяет результаты в один массив
  // Пример использования:
  // let arr = [1, 2, 3];
  // let newArr = arr.flatMap((el) => [el, el * 2]);
  // console.log(newArr); // [1, 2, 2, 4, 3, 6]
  const flatElements = elements.flatMap((el) => el);
  const elementsObj = addObj
    ? flatElements.map((element) => ({ obj: element }))
    : flatElements;
  return JSON.stringify(elementsObj, null, pretty ? 2 : 0);
}

// Пример использования функций для создания компонента
function component() {
  // Пример использования функций
  // Создаем шаблоны фигур с координатами (0, 0)
  const circleTemplate = circle(
    vec2(0, 0),
    20,
    style(colors.RED, colors.BLACK)
  );
  const rectangleTemplate = rectangle(
    vec2(0, 0),
    vec2(70, 100),
    style(colors.PINK, colors.BLACK)
  );

  // Создаем композицию из двух фигур
  // Первая фигура - прямоугольник
  // Вторая фигура - круг
  // Круг смещен относительно прямоугольника на вектор (30, 40)
  const comp1 = [rectangleTemplate, move(circleTemplate, vec2(30, 40))];

  const elements = [
    // Композиция comp1, смещенная на вектор (200, 230)
    move(comp1, vec2(200, 230)),
    // Kомпозиция comp1, смещенная на вектор (340, 230)
    move(comp1, vec2(340, 230)),
    line(vec2(200, 230), vec2(410, 230)),
    line(vec2(200, 330), vec2(410, 330)),
    // Композиция из 3 кругов
    ...clone(
      circle(vec2(220, 27), 20, style(colors.RED, colors.BLACK)),
      3,
      50,
      0
    ),
  ];
  return elements;
}

// Сериализация компонента в JSON
/*
function draw() {
  const component = component();
  return toJson(component, true, true);
}*/
function draw() {
  const component = component();
  scene.sl_obr_cmd(toJson(component, true, true));
}

draw();

