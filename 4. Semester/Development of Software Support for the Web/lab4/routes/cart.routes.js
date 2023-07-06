const express = require('express');
const router = express.Router();
const cart = require('../models/CartModel')
const cartSanitizer = require('./helpers/cart-sanitizer');

// Ulančavanje funkcija međuopreme
router.get('/', cartSanitizer, function (req, res, next) {
    //####################### ZADATAK #######################
    // prikaz košarice uz pomoć cart.ejs

    res.render('cart', {
        title: 'Cart',
        linkActive: 'cart',
        user: req.session.user,
        cart: req.session.cart,
        err: undefined
    })

    //#######################################################
});


router.get('/add/:id', function (req, res, next) {
    //####################### ZADATAK #######################
    //dodavanje jednog artikla u košaricu

    (async () => {
        if ((req.session.cart !== undefined) && (req.session.cart.invalid === true)) 
        {
            delete req.session.cart;
            console.log("Cart in inconsistent state")
            req.session.save(() => {})
        }
        
        if (req.session.cart === undefined)
            req.session.cart = cart.createCart()

        await cart.addItemToCart(req.session.cart, req.params.id, 1)
        res.status(200).end()
    })()

    //#######################################################

});

router.get('/remove/:id', function (req, res, next) {
    //####################### ZADATAK #######################
    //brisanje jednog artikla iz košarice

    (async () => {
        if ((req.session.cart !== undefined && req.session.cart.invalid === true) || req.session.cart === undefined) 
            return

        await cart.removeItemFromCart(req.session.cart, req.params.id, 1)
        res.status(200).end()
    })()

    //#######################################################

});

module.exports = router;