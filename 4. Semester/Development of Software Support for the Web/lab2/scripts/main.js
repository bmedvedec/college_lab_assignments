function refreshCartItems() {
	// INSERT CODE HERE --> PRIPREMA
	let cartItems = document.querySelector('#cart-items');
	let counter = 0;
	if (localStorage.getItem('cart') !== null) 
	{
		let cart = JSON.parse(localStorage.getItem('cart'));
		for (item of cart) 
		{
			counter += item.count;
		}
	}
	cartItems.textContent = counter;
	// END INSERT --> PRIPREMA
}

refreshCartItems();