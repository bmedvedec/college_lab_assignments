// potrebno napisati
const express = require('express')
const app = express()
const db = require('./db')

var path = require('path')

const orderRouter = require('./routes/order.routes')
const homeRouter = require('./routes/home.routes')
const itemRouter = require('./routes/item.routes')

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'ejs')

app.use(express.static(path.join(__dirname, 'public')))
app.use(express.urlencoded( {extended: true }))

app.use('/', homeRouter)
app.use('/order', orderRouter)
app.use('/item', itemRouter)

app.listen(3000)