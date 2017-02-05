# bmptomif_qt
Convert BMP to Altera MIF

https://visuale.ru/blog/chastotomer-s-vga-vykhodom

Одному из наших заказчиков понадобилось измерить частоту сигнала в полевых условиях. Под рукой были только наша плата VE-EP4CE10E и VGA монитор. Пришла идея сделать простенький частотомер с VGA выходом.

Первая проблема с которой мы столкнулись, это способ записи изображения цифр в память FPGA. Блоки памяти можно инициализировать либо *.HEX либо *.MIF файлом. Изображение наших цифр мы решили хранить в 24 битном *.BMP файле. Естественно нам понадобилась программа конвертер из *.BMP в *.MIF. Поискав по просторам интернет ничего стоящего мы не нашли, и решили по быстрому соорудить свою на Qt5. Вот ее код:
