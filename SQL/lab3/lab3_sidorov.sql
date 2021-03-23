-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Сен 17 2020 г., 22:40
-- Версия сервера: 10.3.22-MariaDB
-- Версия PHP: 7.1.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `lab3_sidorov`
--

-- --------------------------------------------------------

--
-- Структура таблицы `employees`
--

CREATE TABLE `employees` (
  `emp_id` int(10) UNSIGNED NOT NULL,
  `name` varchar(20) NOT NULL DEFAULT '',
  `age` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `status` varchar(20) NOT NULL DEFAULT '',
  `comm` decimal(3,2) UNSIGNED NOT NULL DEFAULT 0.00
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `employees`
--

INSERT INTO `employees` (`emp_id`, `name`, `age`, `status`, `comm`) VALUES
(1, 'Пушкин', 25, 'продавец', '0.12'),
(2, 'Лермонтов', 31, 'менеджер', '0.13'),
(3, 'Батюшков', 35, 'менеджер', '0.10'),
(4, 'Гончаров', 28, 'продавец', '0.11'),
(5, 'Радищев', 41, 'маркетолог', '0.15');

-- --------------------------------------------------------

--
-- Структура таблицы `merch`
--

CREATE TABLE `merch` (
  `merc_id` int(10) UNSIGNED NOT NULL,
  `m_name` varchar(20) CHARACTER SET cp1251 NOT NULL DEFAULT '',
  `price` int(10) UNSIGNED NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `merch`
--

INSERT INTO `merch` (`merc_id`, `m_name`, `price`) VALUES
(1, 'Самсунг', 16000),
(2, 'Леново', 12400),
(3, 'Асус', 17200),
(4, 'НР', 18900),
(5, 'Сони', 21000);

-- --------------------------------------------------------

--
-- Структура таблицы `orders`
--

CREATE TABLE `orders` (
  `ord_id` int(10) UNSIGNED NOT NULL,
  `data` date NOT NULL,
  `shop_id` int(10) UNSIGNED NOT NULL,
  `emp_id` int(10) UNSIGNED NOT NULL,
  `merc_id` int(10) UNSIGNED NOT NULL,
  `amount` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `orders`
--

INSERT INTO `orders` (`ord_id`, `data`, `shop_id`, `emp_id`, `merc_id`, `amount`) VALUES
(1, '2020-08-15', 2002, 2, 4, 1),
(2, '2020-08-20', 2003, 1, 1, 2),
(3, '2020-08-25', 2001, 5, 5, 1),
(4, '2020-08-30', 2002, 3, 2, 3),
(5, '2020-09-04', 2004, 2, 1, 3),
(6, '2020-09-05', 2001, 1, 3, 1),
(7, '2020-09-06', 2004, 5, 2, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `shops`
--

CREATE TABLE `shops` (
  `shop_id` int(10) UNSIGNED NOT NULL,
  `name` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `adds` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `director_id` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `shops`
--

INSERT INTO `shops` (`shop_id`, `name`, `adds`, `director_id`) VALUES
(2001, 'Пилот', 'СПб', 5),
(2002, 'Салют', 'Москва', 3),
(2003, 'Электроника', 'Тула', 2),
(2004, 'Сетевой', 'Москва', 2);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `employees`
--
ALTER TABLE `employees`
  ADD PRIMARY KEY (`emp_id`);

--
-- Индексы таблицы `merch`
--
ALTER TABLE `merch`
  ADD PRIMARY KEY (`merc_id`);

--
-- Индексы таблицы `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`ord_id`),
  ADD KEY `fk_shop_id` (`shop_id`),
  ADD KEY `fk_emp_id` (`emp_id`),
  ADD KEY `fk_merc_id` (`merc_id`);

--
-- Индексы таблицы `shops`
--
ALTER TABLE `shops`
  ADD PRIMARY KEY (`shop_id`),
  ADD KEY `fk_director_id` (`director_id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `employees`
--
ALTER TABLE `employees`
  MODIFY `emp_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT для таблицы `merch`
--
ALTER TABLE `merch`
  MODIFY `merc_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT для таблицы `orders`
--
ALTER TABLE `orders`
  MODIFY `ord_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT для таблицы `shops`
--
ALTER TABLE `shops`
  MODIFY `shop_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2005;

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `orders`
--
ALTER TABLE `orders`
  ADD CONSTRAINT `fk_emp_id` FOREIGN KEY (`emp_id`) REFERENCES `employees` (`emp_id`),
  ADD CONSTRAINT `fk_merc_id` FOREIGN KEY (`merc_id`) REFERENCES `merch` (`merc_id`),
  ADD CONSTRAINT `fk_shop_id` FOREIGN KEY (`shop_id`) REFERENCES `shops` (`shop_id`);

--
-- Ограничения внешнего ключа таблицы `shops`
--
ALTER TABLE `shops`
  ADD CONSTRAINT `fk_director_id` FOREIGN KEY (`director_id`) REFERENCES `employees` (`emp_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
