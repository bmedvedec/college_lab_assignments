module.exports =
    class Item {
        constructor(id, name, price, categoryId, imageUrl, colors) {
            this.id = id
            this.name = name
            this.price = price
            this.categoryId = categoryId
            this.imageUrl = imageUrl
            this.colors = colors
        }
    }