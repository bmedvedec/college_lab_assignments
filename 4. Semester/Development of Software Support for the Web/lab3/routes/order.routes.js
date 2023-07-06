// potrebno napisati
var express = require('express')
var router = express.Router()
const repo = require('../repository/repo.db')

router.get('/', (req, res, next) => {
    res.render('order', {
        title: 'Order',
        linkActive: 'order',
        items: repo.items,
        categories: repo.categories
    })
})

module.exports = router