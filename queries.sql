category_by_parent==SELECT * FROM `categories` WHERE parent_id
add_category==INSERT INTO `categories` (`name`, `parent_id`, `description`) VALUES (?, ?, ?)
update_category==UPDATE categories SET name = ?, description = ? WHERE id = ?
delete_category==DELETE FROM `categories` WHERE `categories`.`id`=?

category_products==SELECT products.id, products.product, products.unit, products.price, products.currency, products.source, products.description FROM categories_mapping INNER JOIN products ON categories_mapping.product_id = products.id WHERE categories_mapping.category_id=?

add_product==INSERT INTO `products` (`product`, `unit`, `price`, `currency`, `source`, `description`) VALUES (? , ?, ?, ?, ?, ?)
update_product==UPDATE `products` SET product = ?, unit = ?, price = ?, currency = ?, source = ?, description = ? WHERE id = ?
delete_product==DELETE FROM `products` WHERE `products`.`id`=?
all_products==SELECT * FROM `products`

update_mapping==INSERT INTO `categories_mapping` (`product_id`, `category_id`) VALUES (?, ?)
remove_mapping==DELETE FROM `categories_mapping` WHERE `categories_mapping`.`map_id`=?

contains_in_mapping==SELECT * FROM `categories_mapping` WHERE `product_id`=? AND `category_id`=?
delete_in_mapping==DELETE FROM `categories_mapping` WHERE `product_id`=? AND `category_id`=?
delete_in_mapping_category==DELETE FROM `categories_mapping` WHERE `category_id`=?
contains_category_in_mapping==SELECT * FROM `categories_mapping` WHERE category_id=?
contains_product_in_mapping==SELECT * FROM `categories_mapping` WHERE `product_id`=?
