import * as _ from 'lodash'

let variable: Record<string, any> = {
    'name': 'hh',
    'age': 20,
    'major': 'GIS',
}



let shadowCopy_lodash: Record<string, any> = _.cloneDeep(variable);

console.log(shadowCopy_lodash);