// potrebno napisati
var express = require('express')
var router = express.Router()
const repo = require('../repository/repo.db')

router.get('/:id([0-9]+)', (req, res, next) => {
    let id = parseInt(req.params.id)
    let item = repo.getItem(id)
    let category = repo.getCategory(item.categoryId)

    res.render('item', {
        linkActive: 'order',
        title: item.name,
        item: item,
        category: category
    })
})

module.exports = router