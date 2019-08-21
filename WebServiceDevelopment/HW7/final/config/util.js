var DATE1 = new Array(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28);
var DATE2 = DATE1.concat([29,30]);
var DATE3 = DATE1.concat([29,30,31]);

module.exports = {
//--------------- mySQL query ----------------
// USER ID INDEX QUERY
uid_query : "SELECT id FROM users WHERE uid=?",

// Insert Query
// parameter: uid, date, money, detail, class
insertQuery : "INSERT INTO final(uid,date,money,detail,class) VALUES(?,?,?,?,?)",

// basic Search Query
// parameter: id
searchQuery : "SELECT * FROM final WHERE id=? AND uid=?",

// basic Update Query
// parameter: id
updateQuery : "UPDATE final SET date=?,money=?,detail=?,class=? WHERE id=? AND uid=?",

// basic Delete Query
// parameter: id
deleteQuery : "DELETE FROM final WHERE id = ? AND uid=?",

// TOTAL QUERY
// 7 days total query parameter: uid / return: total
week_total_query : "SELECT SUM(money) as total FROM final WHERE uid=? AND TO_DAYS(NOW())-TO_DAYS(date) <=7",

// month total query parameter: uid, year, month / return total
month_total_query : "SELECT SUM(money) as total FROM final WHERE uid=? AND YEAR(date)=? AND MONTH(date)=?",

// year total query parameter: uid, year / return total
year_total_query : "SELECT SUM(money) as total FROM final WHERE uid=? AND YEAR(date)=?",

// PIE QUERY
// 7 days pie query parameter: uid / return: total, class
week_pie_query : "SELECT SUM(money) as total, class FROM final WHERE uid=? AND TO_DAYS(NOW())-TO_DAYS(date) <=7 GROUP BY class ORDER BY SUM(money) DESC",
// month pie query parameter: uid, year, month / return: total, class
month_pie_query : "SELECT SUM(money) as total, class FROM final WHERE uid=? AND YEAR(date)=? AND MONTH(date)=? GROUP BY class ORDER BY SUM(money) DESC",
// year pie query parameter: uid, year / return: total, class
year_pie_query : "SELECT SUM(money) as total, class FROM final WHERE uid=? AND YEAR(date)=? GROUP BY class ORDER BY SUM(money) DESC",

// BAR QUERY
// 7 days bar query parameter: uid / return: day, total
week_bar_query : "SELECT DAY(date) as day,SUM(money) as total FROM final WHERE uid=? AND TO_DAYS(NOW())-TO_DAYS(date) <=7 GROUP BY date ORDER BY date",
// month bar query parameter: uid, year, month / return: day, total
month_bar_query : "SELECT DAY(date) as day,SUM(money) as total FROM final WHERE uid=? AND YEAR(date)=? AND MONTH(date)=? GROUP BY DAY(date) ORDER BY DAY(date)",
// year bar query parameter: uid, year / return: month, total
year_bar_query : "SELECT MONTH(date) as month,SUM(money) as total FROM final WHERE uid=? AND YEAR(date)=? GROUP BY MONTH(date) ORDER BY MONTH(date)",

// TABLE QUERY
// 7 days table query parameter: uid
week_table_query : "SELECT id,date,money,detail,class FROM final WHERE uid=? AND TO_DAYS(NOW())-TO_DAYS(date) <=7 ORDER BY date",
// month table query parameter: uid, year, month
month_table_query : "SELECT id,date,money,detail,class FROM final WHERE uid=? AND YEAR(date)=? AND MONTH(date)=? ORDER BY date",
// year table query parameter: uid, year
year_table_query : "SELECT id,date,money,detail,class FROM final WHERE uid=? AND YEAR(date)=? ORDER BY date",

// --------------- label variable -------------

MONTH : {'JAN':DATE3, 'FEB':DATE1, 'MAR':DATE3, 'APR':DATE2, 'MAY':DATE3, 'JUN':DATE2, 'JUL':DATE3, 'AUG':DATE3, 'SEP':DATE2, 'OCT':DATE3, 'NOV':DATE2, 'DEC':DATE3 },

YEAR : ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC'],

// ------------ Helper Function -----------------

isLoggedIn: function(req, res, next) {
    if (req.isAuthenticated()){
        return next();
    } else {
        res.redirect('../pages/signin');
    }
},

}