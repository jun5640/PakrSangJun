var ServerRequest = function (data, callback) {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.open("POST", "/");
    xmlhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            callback(JSON.parse(this.responseText));
        }
    };
    xmlhttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xmlhttp.send(JSON.stringify(data));
};

function isEmpty(str) {
    return (!str || 0 === str.length);
}

function isBlank(str) {
    return (!str || /^\s*$/.test(str));
}

if (!String.prototype.format) {
    String.prototype.format = function () {
        var args = arguments;
        return this.replace(/{(\d+)}/g, function (match, number) {
            return typeof args[number] != 'undefined' ? args[number] : match;
        });
    };
}

if (!String.prototype.isEmpty) {
    String.prototype.isEmpty = function () {
        return (this.length === 0 || !this.trim());
    };
}

if (!Array.prototype.swap) {
    Array.prototype.swap = function (x, y) {
        var b = this[x];
        this[x] = this[y];
        this[y] = b;
        return this;
    }
}
