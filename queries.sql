parent_category==SELECT * FROM `categories` WHERE parent_id IS NULL
category_by_parent==SELECT * FROM `categories` WHERE parent_id=?
category_products==SELECT * FROM categories_mapping INNER JOIN products ON categories_mapping.product_name = products.product WHERE categories_mapping.category_id=?
add_category==INSERT INTO `categories` (`id`, `name`, `parent_id`, `description`) VALUES (?, ?, ?, ?)
add_product==INSERT INTO `products` (`product`, `unit`, `price`, `currency`) VALUES (? , ?, ?, ?)
delete_category==DELETE FROM `categories` WHERE `categories`.`id`=?
delete_product==DELETE FROM `products` WHERE `products`.`product`=?
update_mapping==INSERT INTO `categories_mapping` (`map_id`, `product_name`, `category_id`) VALUES (?, ?, ?)
remove_mapping==DELETE FROM `categories_mapping` WHERE `categories_mapping`.`map_id`=?
contains_in_mapping==SELECT * FROM `categories_mapping` WHERE `product_name` LIKE ? AND `category_id` LIKE ?
contains_category_in_mapping==SELECT * FROM `categories_mapping` WHERE `product_name` LIKE ? AND `category_id` LIKE ?
contains_product_in_mapping==SELECT * FROM `categories_mapping` WHERE `product_name` LIKE ? AND `category_id` LIKE ?
