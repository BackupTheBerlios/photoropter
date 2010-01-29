#ifndef __CHANNEL_TYPES_H__
#define __CHANNEL_TYPES_H__

namespace phtr
{

    /**
    * \brief Struct containing channel designations.
    * \note The class contains an enum which defines the actual channels.
    */
    struct Channel
    {

        /**
        * \brief The actual enum containing channel designations.
        */
        enum type
        {

            /**
            * \brief The 'red' channel.
            */
            red = 0,
            /**
            * \brief The 'green' channel.
            */
            green,
            /**
            * \brief The 'blue' channel.
            */
            blue

        }; // enum Channel::type

    }; // class Channel

} // namespace phtr

#endif // __CHANNEL_TYPES_H__
