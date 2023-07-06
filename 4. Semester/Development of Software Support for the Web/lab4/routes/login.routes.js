const express = require('express');
const router = express.Router();
const User = require('../models/UserModel')


router.get('/', function (req, res, next) {
    //####################### ZADATAK #######################
    //vrati login stranicu

    res.render('login', {
        linkActive: 'login',
        user: req.session.user,
        err: req.session.err
    });

    //#######################################################

});

router.post('/', function (req, res, next) {
    //####################### ZADATAK #######################
    //postupak prijave korisnika
    
    (async () => {
        let user = await User.fetchByUsername(req.body.user)

        if (user.id === undefined) 
        {
            res.render('Login', {
                title: 'Log in',
                linkActive: 'login',
                user: req.session.user,
                err: 'Unknown username'
            });

            return
        }

        if (!user.checkPassword(req.body.password)) 
        {
            res.render('Login', {
                title: 'Log in',
                linkActive: 'login',
                user: req.session.user,
                err: 'Incorrect password'
            });
            
            return
        }

        req.session.user = user
        res.redirect('/')
    })();

    //#######################################################

});


module.exports = router;