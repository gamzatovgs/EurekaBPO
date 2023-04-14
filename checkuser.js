const checkuser = require('bindings')('checkuser')
const express = require('express')
const app = express()
const urlencodedParser = express.urlencoded({extended: false})

app.get('/', function (request, response) {
    response.sendFile(__dirname + '/index.html')
})

app.post('/', urlencodedParser, function (request, response) {
    if(!request.body)
        return response.sendStatus(400)

    const userName = request.body.userName

    if(checkuser.check(userName)) {
        console.log(userName + ' = true')
        response.send(`
            <div align="center">
                <br>
                <h1>Пользователь \< ` + userName + ` \> есть</h1>
                <input type="button" onclick="history.back();" value="Назад"/>                
            </div>
        `)
    } else {
        console.log(userName + ' = false')
        response.send(`
            <div align="center">
                <br>
                <h1>Пользователя \< ` + userName + ` \> нет</h1>
                <input type="button" onclick="history.back();" value="Назад"/>
            </div>
        `)
    }
})

app.listen(3000, () => {
    console.log('Server has been started...')
})