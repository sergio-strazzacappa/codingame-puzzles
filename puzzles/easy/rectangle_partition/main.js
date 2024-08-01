let rectangle = {
    w: 0,
    h: 0,
    count_x: 0,
    count_y: 0,
    mesurements_x: [],
    mesurements_y: [],
    debug: function() {
        console.error(
            'w: ' + this.w +
            '\nh: ' + this.h +
            '\ncount_x: ' + this.count_x +
            '\ncount_y: ' + this.count_y +
            '\nmesurements_x: ' + this.mesurements_x +
            '\nmesurements_y: ' + this.mesurements_y
        );
    }
};

function read_input() {
    let inputs = readline().split(' ');

    rectangle.w = parseInt(inputs[0]);
    rectangle.h = parseInt(inputs[1]);
    rectangle.count_x = parseInt(inputs[2]);
    rectangle.count_y = parseInt(inputs[3]);

    inputs = readline().split(' ');

    rectangle.mesurements_x.push(0);

    for (let i = 0; i < rectangle.count_x; i++) {
        rectangle.mesurements_x.push(parseInt(inputs[i]));
    }

    rectangle.mesurements_x.push(rectangle.w);

    inputs = readline().split(' ');
    
    rectangle.mesurements_y.push(0);

    for (let i = 0; i < rectangle.count_y; i++) {
        rectangle.mesurements_y.push(parseInt(inputs[i]));
    }

    rectangle.mesurements_y.push(rectangle.h);
}

function solve() {
    let squares = 0;

    let xs = [];
    let ys = [];

    for (let i = 0; i < rectangle.mesurements_x.length; i++) {
        for (let j = i + 1; j < rectangle.mesurements_x.length; j++) {
            let w = rectangle.mesurements_x[j] - rectangle.mesurements_x[i];
            xs.push(w);
        }
    }

    for (let i = 0; i < rectangle.mesurements_y.length; i++) {
        for (let j = i + 1; j < rectangle.mesurements_y.length; j++) {
            let h = rectangle.mesurements_y[j] - rectangle.mesurements_y[i];
            ys.push(h);
        }
    }

    for (let i = 0; i < xs.length; i++) {
        for (let j = 0; j < ys.length; j++) {
            if (xs[i] === ys[j]) {
                squares++;
            } 
        }
    }
    console.log(squares);
}

function main() {
    read_input();
    rectangle.debug();
    solve();
}

main()