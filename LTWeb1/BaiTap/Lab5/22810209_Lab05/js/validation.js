(function () {
    var password = document.getElementById("password");
    var passwordConfirm = document.getElementById("password-confirm");

    var checkPasswordValidity = function() {
        if (password.value != passwordConfirm.value) {
            passwordConfirm.setCustomValidity('Passwords must match.')
        } else {
            passwordConfirm.setCustomValidity('')
        }
    };

    password.onchange = checkPasswordValidity;
    passwordConfirm.onchange = checkPasswordValidity;
}());