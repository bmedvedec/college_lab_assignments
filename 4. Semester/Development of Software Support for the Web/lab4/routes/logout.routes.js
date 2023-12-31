const express = require('express');
const router = express.Router();

router.get('/', function (req, res, next) {
    //####################### ZADATAK #######################
    // - obrisati sadržaj košarice
    // - odjaviti registriranog korisnika iz sustava
    // - napraviti redirect na osnovnu stranicu

    if (req.session.cart !== undefined)
        req.session.cart.invalid = true

    req.session.user = undefined

    req.session.destroy((error) => {
        if (error) 
        {
            console.log(error)
            res.sendStatus(500)
        } 
        else 
        {
            res.redirect('/')
        }
    });

    //#######################################################
});

module.exports = router;