function addToCart(id) {
	// INSERT CODE HERE --> PRIPREMA
	if (localStorage.getItem('cart') === null) 
	{
		let cart = [{"id": id, "count": 1}];
		localStorage.setItem('cart', JSON.stringify(cart));
	} else 
	{
		cart = JSON.parse(localStorage.getItem('cart'));
		let found = false;
		for (item of cart) 
		{
			if (item.id === id) 
			{
				found = true;
				item.count++;
			}
		}
		if (found === false) 
		{
			cart.push({"id": id, "count": 1});
		}

		localStorage.setItem('cart', JSON.stringify(cart));
	}
	// END INSERT --> PRIPREMA
	refreshCartItems();
}

let getData = async function () {
	let response = await fetch("data/lab2.json");
	let data = await response.json();
	addCategories(data);
}

let addCategories = async function (data) {
	let categories = data.categories;
	let main = document.querySelector('main');
	let categoryTemplate = document.querySelector('#category-template');

	for (let index = 0; index < categories.length; index++) {
		let category = categoryTemplate.content.cloneNode(true);
		let categoryTitleElement = category.querySelector('.decorated-title > span');
		categoryTitleElement.textContent = categories[index].name;

		let products = data.products.filter(p => p.categoryId == categories[index].id);

		//console.log(products);

		// INSERT CODE HERE --> PRIPREMA
		let gallery = category.querySelector('.gallery');
		let productTemplate = document.querySelector('#product-template');

		for (let i = 0; i < products.length; i++) {
			let product = productTemplate.content.cloneNode(true);

			let photo_box = product.querySelector('.photo-box');
			photo_box.setAttribute("data-id", products[i].id);

			let photo_box_image = product.querySelector('.photo-box-image');
			photo_box_image.src = products[i].imageUrl;

			let photo_box_title = product.querySelector('.photo-box-title');
			photo_box_title.textContent = products[i].name;

			let cart_btn = product.querySelector('.cart-btn');
			cart_btn.addEventListener("click", () => {
				addToCart(products[i].id)
			});

			gallery.appendChild(product);
		}
		// END INSERT --> PRIPREMA

		main.appendChild(category);
	}
};
getData();