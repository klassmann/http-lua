-- Application

styles = [[
    body {
        background-color: #EEFFEE;
        color: #ffffff;
        text-shadow: 1px 1px #000000;
        display: flex;
        justify-content: center;
    }

    .center {
        display: flex;
        justify-content: center;
        flex-flow: column wrap;
        width: 800px;
    }



    a {
        color: #FFFFFF;
    }

    a:visited {
        color: orange;
    }
]]

menu = [[
    <ul>
        <li><a href="/">Home</a></li>
        <li><a href="/article">Articles</a></li>
        <li><a href="/about">About</a></li>
    </ul>
]]

base = [[
<html>
<head>
    <title>Lua Application</title>
    <link rel="stylesheet" href="/styles.css">
</head>
    <body>
        <div class="center">
            <h1>Welcome from my <span style="color: blue">Lua</span> application</h1>
            %s
            <p>Method: <b>%s</b></p>
            <p>Path: <b>%s</b></p>
            <p>Host: %s</p>
            <p>User Agent: %s</p>
        </div>
    </body>
</html>
]]


function route(request)

    if request.path == '/styles.css' then
        return 200, styles
    end

    return 200, string.format(
            base,
            menu,
            request.method,
            request.path,
            request.headers["Host"],
            request.headers["User-Agent"]
    )
end