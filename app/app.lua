-- Application

io = require("io")

styles = [[
    body {
        line-height: 1.1rem;
        font-size: 1.2rem;
        font-family: sans;
        background-color: #222222;
        color: white;
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
        color: dodgerblue;
    }

    a:visited {
        color: steelblue;
    }

    .navbar {
        display: flex;
        list-style: none;
        justify-content: space-evenly;
    }
]]

base = [[
<html>
<head>
    <title>Lua Application</title>
    <link rel="stylesheet" href="/styles.css">
</head>
    <body>
        <div class="center">
            <div style="width: 300px;">
            %s
            </div>
            <h1>Welcome to my <span style="color: dodgerblue">Lua</span> application</h1>
            <p><a target="_blank" href="http://www.lua.org/manual/5.3/">Lua 5.3 Reference Manual</a></p>
            <p>Method: <b>%s</b></p>
            <p>Path: <b>%s</b></p>
            <p>Host: %s</p>
            <p>User Agent: %s</p>
        </div>
    </body>
</html>
]]

function load_logo()
    local f = io.open("app/static/http-lua.svg", "r")
    if f ~= nil then
        local content = f:read("a")
        f:close()
        return content
    else
        return ""
    end
end

function index(request)

    if request.path == '/styles.css' then
        return 200, styles
    end

    return 200, string.format(
            base,
            load_logo(),
            request.method,
            request.path,
            request.headers["Host"],
            request.headers["User-Agent"]
    )
end