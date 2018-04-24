parent_category==SELECT * FROM `categories` WHERE parent_id IS NULL
category_by_parent==SELECT * FROM `categories` WHERE parent_id%
category_products==SELECT * FROM categories_mapping INNER JOIN products ON categories_mapping.product_name = products.product WHERE categories_mapping.category_id%
