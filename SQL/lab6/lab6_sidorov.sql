-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Окт 31 2020 г., 23:51
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
-- Дублирующая структура для представления `avg_sum`
-- (См. Ниже фактическое представление)
--
CREATE TABLE `avg_sum` (
`Employee_name` varchar(20)
,`Average_sum` decimal(46,4)
);

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
-- Дублирующая структура для представления `itog_query`
-- (См. Ниже фактическое представление)
--
CREATE TABLE `itog_query` (
`Order_ID` int(10) unsigned
,`Order_date` date
,`Shop_name` varchar(20)
,`Employee_name` varchar(20)
,`Merch_name` varchar(20)
,`Order_amount` int(10) unsigned
);

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

-- --------------------------------------------------------

--
-- Структура для представления `avg_sum`
--
DROP TABLE IF EXISTS `avg_sum`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `avg_sum`  AS  select `employees`.`name` AS `Employee_name`,avg(`summ`.`sum`) AS `Average_sum` from ((((`employees` join `orders`) join `merch`) join `shops`) join (select `employees`.`name` AS `name`,sum(`orders`.`amount` * `merch`.`price`) AS `sum` from (((`employees` join `orders`) join `merch`) join `shops`) where `orders`.`shop_id` = `shops`.`shop_id` and `orders`.`emp_id` = `employees`.`emp_id` and `orders`.`merc_id` = `merch`.`merc_id` group by 1) `summ`) where `orders`.`shop_id` = `shops`.`shop_id` and `orders`.`emp_id` = `employees`.`emp_id` and `orders`.`merc_id` = `merch`.`merc_id` group by 1 ;

-- --------------------------------------------------------

--
-- Структура для представления `itog_query`
--
DROP TABLE IF EXISTS `itog_query`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `itog_query`  AS  select `orders`.`ord_id` AS `Order_ID`,`orders`.`data` AS `Order_date`,case when `orders`.`shop_id` = `shops`.`shop_id` then `shops`.`name` end AS `Shop_name`,case when `orders`.`emp_id` = `employees`.`emp_id` then `employees`.`name` end AS `Employee_name`,case when `orders`.`merc_id` = `merch`.`merc_id` then `merch`.`m_name` end AS `Merch_name`,`orders`.`amount` AS `Order_amount` from (((`orders` join `employees`) join `merch`) join `shops`) where `orders`.`shop_id` = `shops`.`shop_id` and `orders`.`emp_id` = `employees`.`emp_id` and `orders`.`merc_id` = `merch`.`merc_id` ;

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
