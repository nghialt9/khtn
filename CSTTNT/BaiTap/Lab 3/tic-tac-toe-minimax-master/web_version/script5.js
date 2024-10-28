var board = Array.from({ length: 5 }, () => Array(5).fill(0));

var HUMAN = -1;
var COMP = +1;

/* Function to heuristic evaluation of state. */
function evaluate(state) {
	var score = 0;

	if (gameOver(state, COMP)) {
		score = +1;
	} else if (gameOver(state, HUMAN)) {
		score = -1;
	} else {
		score = 0;
	}

	return score;
}

/* This function tests if a specific player wins */
function gameOver(state, player) {
	for (var x = 0; x < 5; x++) {
		for (var y = 0; y < 5; y++) {
			if (state[x][y] === player) {
				// Check horizontal
				if (y <= 2 && checkLine(state, player, x, y, 0, 1)) return true;
				// Check vertical
				if (x <= 2 && checkLine(state, player, x, y, 1, 0)) return true;
				// Check diagonal /
				if (x <= 2 && y >= 2 && checkLine(state, player, x, y, 1, -1)) return true;
				// Check diagonal \
				if (x <= 2 && y <= 2 && checkLine(state, player, x, y, 1, 1)) return true;
			}
		}
	}
	return false;
}

function checkLine(state, player, startX, startY, deltaX, deltaY) {
	for (var i = 0; i < 3; i++) {
		if (state[startX + i * deltaX][startY + i * deltaY] !== player) {
			return false;
		}
	}
	return true;
}

/* This function test if the human or computer wins */
function gameOverAll(state) {
	return gameOver(state, HUMAN) || gameOver(state, COMP);
}

function emptyCells(state) {
	var cells = [];
	for (var x = 0; x < 5; x++) {
		for (var y = 0; y < 5; y++) {
			if (state[x][y] == 0) cells.push([x, y]);
		}
	}
	return cells;
}

/* A move is valid if the chosen cell is empty */
function validMove(x, y) {
	return board[x] && board[x][y] == 0;
}

/* Set the move on board, if the coordinates are valid */
function setMove(x, y, player) {
	if (validMove(x, y)) {
		board[x][y] = player;
		return true;
	} else {
		return false;
	}
}

/* *** AI function that choice the best move *** */
function minimax(state, depth, player) {
	var best;

	if (player == COMP) {
		best = [-1, -1, -1000];
	} else {
		best = [-1, -1, +1000];
	}

	if (depth === 0 || gameOverAll(state)) {
		var score = evaluate(state);
		return [-1, -1, score];
	}

	emptyCells(state).forEach(function (cell) {
		var x = cell[0];
		var y = cell[1];
		state[x][y] = player;
		var score = minimax(state, depth - 1, -player);
		state[x][y] = 0; // Restore state
		score[0] = x;
		score[1] = y;

		if (player == COMP) {
			if (score[2] > best[2]) best = score;
		} else {
			if (score[2] < best[2]) best = score;
		}
	});

	return best;
}

/* It calls the minimax function */
function aiTurn() {
	var x, y;
	var move;
	var cell;

    // Chọn độ sâu hợp lý
	const depth = Math.min(emptyCells(board).length, 25); // Giới hạn độ sâu

	if (emptyCells(board).length == 25) {
		x = parseInt(Math.random() * 5);
		y = parseInt(Math.random() * 5);
	} else {
		move = minimax(board, depth, COMP);
		x = move[0];
		y = move[1];
	}

	if (setMove(x, y, COMP)) {
		cell = document.getElementById(String(x) + String(y));
		cell.innerHTML = "O";
	}
}

/* main */
function clickedCell(cell) {
	var button = document.getElementById("bnt-restart");
	button.disabled = true;
	var conditionToContinue = gameOverAll(board) == false && emptyCells(board).length > 0;

	if (conditionToContinue) {
		var x = cell.id.split("")[0];
		var y = cell.id.split("")[1];
		var move = setMove(x, y, HUMAN);
		if (move) {
			cell.innerHTML = "X";
			if (conditionToContinue) aiTurn();
		}
	}
	if (gameOver(board, COMP)) {
		highlightWinningLine(COMP);
		var msg = document.getElementById("message");
		msg.innerHTML = "You lose!";
	}
	if (emptyCells(board).length == 0 && !gameOverAll(board)) {
		var msg = document.getElementById("message");
		msg.innerHTML = "Draw!";
	}
	if (gameOverAll(board) || emptyCells(board).length == 0) {
		button.value = "Restart";
		button.disabled = false;
	}
}

function highlightWinningLine(player) {
	for (var x = 0; x < 5; x++) {
		for (var y = 0; y < 5; y++) {
			if (board[x][y] === player) {
				// Check horizontal
				if (y <= 2 && checkLine(board, player, x, y, 0, 1)) {
					for (let i = 0; i < 3; i++) {
						document.getElementById((x) + "" + (y + i)).style.color = "red";
					}
					return;
				}
				// Check vertical
				if (x <= 2 && checkLine(board, player, x, y, 1, 0)) {
					for (let i = 0; i < 3; i++) {
						document.getElementById((x + i) + "" + (y)).style.color = "red";
					}
					return;
				}
				// Check diagonal /
				if (x <= 2 && y >= 2 && checkLine(board, player, x, y, 1, -1)) {
					for (let i = 0; i < 3; i++) {
						document.getElementById((x + i) + "" + (y - i)).style.color = "red";
					}
					return;
				}
				// Check diagonal \
				if (x <= 2 && y <= 2 && checkLine(board, player, x, y, 1, 1)) {
					for (let i = 0; i < 3; i++) {
						document.getElementById((x + i) + "" + (y + i)).style.color = "red";
					}
					return;
				}
			}
		}
	}
}

/* Restart the game */
function restartBnt(button) {
	if (button.value == "Start AI") {
		aiTurn();
		button.disabled = true;
	} else if (button.value == "Restart") {
		var htmlBoard;
		var msg;

		for (var x = 0; x < 5; x++) {
			for (var y = 0; y < 5; y++) {
				board[x][y] = 0;
				htmlBoard = document.getElementById(String(x) + String(y));
				htmlBoard.style.color = "#444";
				htmlBoard.innerHTML = "";
			}
		}
		button.value = "Start AI";
		msg = document.getElementById("message");
		msg.innerHTML = "";
	}
}
