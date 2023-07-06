const {Result} = require('express-validator')
const db = require('../db')
const Category = require('../models/category.model')
const Item = require('../models/item.model')

class Repo {
    constructor() {
        this.seedRepo()
    }

    async seedRepo() {
        await this.seedCategories()
        await this.seedItems()
    }

    async seedCategories() {
        this.categories = []

        let query = `SELECT * FROM categories`
        let response = await db.query(query)
        let rows = response.rows

        for (let row of rows) {
            let newCategory = new Category(row.id, row.name, row.description, row.seasonal)
            this.categories.push(newCategory)
        }
    }

    async seedItems() {
        this.items = []

        let query = `SELECT * FROM inventory`
        let response = await db.query(query)
        let rows = response.rows

        for (let row of rows) {
            let newItem = new Item(row.id, row.name, row.price, row.categoryid, row.imageurl, row.colors)
            this.items.push(newItem)
        }
    }

    getItem(id) {
        return this.items.find(i => i.id === id)
    }

    getCategory(id) {
        return this.categories.find(i => i.id === id)
    }
}

const repoInstance = new Repo();
module.exports = repoInstance