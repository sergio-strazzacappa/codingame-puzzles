// the number of temperatures to analyse
const n = parseInt(readline());

// temperature closest to zero
let closestTemperature = 0;

let inputs = readline().split(' ');

for (let i = 0; i < n; i++) {
	// a temperature expressed as an integer ranging from -273 to 5526
	const t = parseInt(inputs[i]);

	if (i === 0) {
		closestTemperature = t;
	} else if (Math.abs(t) < Math.abs(closestTemperature)) {
		closestTemperature = t;
	} else if (Math.abs(t) === Math.abs(closestTemperature)) {
		closestTemperature = t > closestTemperature ? t : closestTemperature;
	}
}

console.log(closestTemperature);
